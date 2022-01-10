## markovich

A demonstration of using offline-trained trigram markov chains to generate procedural words efficiently at runtime; for example, to produce names for planets, regions, weapons or cities in games.

Markovich consists of a Golang data conditioning and code generation tool coupled with a C++ runtime component that integrates [ChaiScript](https://github.com/ChaiScript) for experimenting with the generation functions more interactively. 

The approach used here is based upon one deployed in a very large procedural video game; important pillars include:

* Very fast generation with a known (low) memory overhead
* Easy to tune, iterate, test and experiment 
* Support for 'themeing' the generated text by switching different training data on the fly, even mid-word
* Ways to limit obscenities in the resulting text

.. and of course, *good quality names*. But what makes a good name? What even is a name? In what language? Or genre? Is `Mpho` a good name, or `James` - to whom? Why?

.. it is surprisingly easy to disappear down a reductionist spiral when trying to talk about this topic. It touches on numerous branches of linguistics, visual communication, language history and more. One man's name is another's confusing stream of unrecognisable glyphs.

Therefore, Markovich narrows down to producing ASCII-only 'recognisably/pronouncably western' names. Partially because I have English as my primary language, I would find it impossible to reliably tune a generator that worked only in Korean Hangul.

Some curated examples from Markovich:

. | . | . | .
--- | --- | --- | ---
`aisyanis` | `glevitassol` | `birumobanoti` | `hitoris`
`omsakhamna` | `umaratibane` | `supuriharu` | `scef-y-gra`
`ires'kohoreto` | `geniponori` | `eishichemino` | `kalaitho`
`imiculeno-ba` | `rogayamana` | `reengill` | `esikyel'dor`



<br><hr><br>
## Method

<br>

### Conjuring

So how do we fashion a word out of thin air?

A naive approach might be to just choose N random letters:

```bplahqggn```

Is that a good word? Even without getting deep into quality grading we can probably agree that by most measures, no, it looks like a bunch of random letters. Picking arbitrary single letters one at a time means stumbling upon a pleasing and viable result is fairly unlikely.

Adding a basic rule to this process could improve matters. Instead of a random letter, we first decide on a sequence of consonants (*C*) and vowels (*V*), according to a layout that mimics common word construction - eg. **CVCCVCCV**. When picking letters, this then reduces the chance of having irregular and undesired patterning, like 6 consonants in a row. 

```Fawsiklub```

```Zocmesxol```

These do feel a little better, but we have to still rely on chance to get common, recognisable [digraphs](https://en.wikipedia.org/wiki/Digraph_(orthography)) such as 'th' or 'qu'.


To tackle that, how about we start with some degree of predetermined structure - a set of short, manually crafted 'building blocks' - and then append a few in random order?

![blocks <>](/doc/block-demo1.svg "Blocks")

This is immediately more successful. Initially seeding with good structure begets better structured results. However, without a large number of building blocks patterns may become visible and the results may become stale and repetitive - plus, someone has to go generate all those blocks by hand? Could we get a machine to do it instead? 

Instead of dealing with indivisible blocks, our chosen method will take in lists of existing words as training data and derive a probability distribution table. This can tell us viable subsequent letters, given a current state - eg. if the *last three letters* we have in our word are ```VIK```, the table may tell us that ```T``` is the most common following letter, with ```H```, ```I``` or ```O``` being less so:

![markov <>](/doc/markov-demo1.svg "Markov")

We then use some decision function to choose one (potentially just at random) - ```H``` - append it and repeat the process with our new *last three letters* - ```IKH```. Repeat until you have a long enough word.

In this way, we build words a letter-at-a-time but with informed knowledge of what choices are most appropriate. Common digraphs will appear because the frequency of, say, ```h``` following ```t``` will be higher if we are using English training data.

This is known as an [n-gram](https://en.wikipedia.org/wiki/N-gram) probabilistic language model where N in our case is 4, a sweet-spot balance between too fragmented (lower N) and too formulaic (higher N). The initial generation process is considered a [Markov chain](https://en.wikipedia.org/wiki/Markov_chain), hence the silly name of the project.

<br>

### Training

(Referenced code below can be found in [offline/freqdata.go](offline/freqdata.go))

The offline analysis tool takes in plain word lists and produces frequency tables that are then baked out into generated code.

Each line in a candidate list of names is run through ```processString```, which walks the input string in blocks of 4 characters and records each one in a unique list of fragments.

Once all fragments have been collected across all input files, we then loop across the fragment collection and begin recording the probabilities - building a lookup table where the key is the leading 3 characters and it points to a frequency table of occurrences of the fourth. In **tablegen**, the ```buildTrigramData``` function is called per-fragment and returns a ```byte:float32``` map of character to probability weighting.

![fragmenting <>](/doc/fragment.svg "Fragment")

Given fragment ```GRAN```, trigram entry ```GRA``` adds ```N``` to its list of possible following letters. If ```N``` was already stored, we increase the weighting on it to indicate that it turns up more often after the sequence ```GRA```.

![trigram <>](/doc/trigram.svg "Trigram")

Once all fragments across all inputs have been processed, we are left with a huge table of trigrams, each entry pointing to weighting for all subsequent characters encountered. This is all we need to move on to doing code generation for the runtime - however there may be other things we can do with this table.

#### Smoothing

Even with huge input lists, there will inevitably be trigrams that end up with only a single potential character - '*infrequent grams*'. These are undesirable as they can only produce the same output each time, and that's boring. To tackle this, additional post-process [*smoothing techniques*](https://en.wikipedia.org/wiki/N-gram#Smoothing_techniques) can be designed to help add entropy back in.

**tablegen** contains an example - ```applyOneBranchSmoothing()``` - which, while simple, does a reasonable job of reducing the number of isolated choices. The approach is as follows:

* For a given problematic trigram + single branch - lets say ```ARN -> U``` - take the last two letters of the trigram, ```RN```
* Search through all the other trigrams for ones *beginning with* ```RN```
* Steal their 3rd character as a new branch for our original problematic trigram
* ... which means that all the new branches will definitely feed into existing trigrams in the table during generation - we don't just choose random characters, as they might have *no* onward matches, not really improving matters.

![smoothing <>](/doc/smoothing.svg "Smoothing")