// ------------------------------------------------------------------------------------------------
// aleaPRNG 1.1
// ------------------------------------------------------------------------------------------------
// Copyright (c) 2017-2020, W. "Mac" McMeans
// LICENSE: BSD 3-Clause License
// https://github.com/macmcmeans/aleaPRNG/blob/master/aleaPRNG-1.1.min.js
// ------------------------------------------------------------------------------------------------
function aleaPRNG(){return function(n){"use strict";var r,t,e,o,a,u=new Uint32Array(3),i="";function c(n){var a=function(){var n=4022871197,r=function(r){r=r.toString();for(var t=0,e=r.length;t<e;t++){var o=.02519603282416938*(n+=r.charCodeAt(t));o-=n=o>>>0,n=(o*=n)>>>0,n+=4294967296*(o-=n)}return 2.3283064365386963e-10*(n>>>0)};return r.version="Mash 0.9",r}();r=a(" "),t=a(" "),e=a(" "),o=1;for(var u=0;u<n.length;u++)(r-=a(n[u]))<0&&(r+=1),(t-=a(n[u]))<0&&(t+=1),(e-=a(n[u]))<0&&(e+=1);i=a.version,a=null}function f(n){return parseInt(n,10)===n}var l=function(){var n=2091639*r+2.3283064365386963e-10*o;return r=t,t=e,e=n-(o=0|n)};return l.fract53=function(){return l()+1.1102230246251565e-16*(2097152*l()|0)},l.int32=function(){return 4294967296*l()},l.cycle=function(n){(n=void 0===n?1:+n)<1&&(n=1);for(var r=0;r<n;r++)l()},l.range=function(){var n,r;return 1===arguments.length?(n=0,r=arguments[0]):(n=arguments[0],r=arguments[1]),arguments[0]>arguments[1]&&(n=arguments[1],r=arguments[0]),f(n)&&f(r)?Math.floor(l()*(r-n+1))+n:l()*(r-n)+n},l.restart=function(){c(a)},l.seed=function(){c(Array.prototype.slice.call(arguments))},l.version=function(){return"aleaPRNG 1.1.0"},l.versions=function(){return"aleaPRNG 1.1.0, "+i},0===n.length&&(window.crypto.getRandomValues(u),n=[u[0],u[1],u[2]]),a=n,c(n),l}(Array.prototype.slice.call(arguments))}


// ------------------------------------------------------------------------------------------------
// Markovich generation utilities; ported from C++
// ------------------------------------------------------------------------------------------------

const ALL_VOWELS = Object.freeze(['a', 'e', 'i', 'o', 'u', 'y']);
const SEPARATORS = Object.freeze(['\'', '-']);

function chooseRandomVowel(rngInstance, includeY = false) {
    const choiceIndex = rngInstance.range(includeY ? 5 : 4)
    return ALL_VOWELS[choiceIndex];
}
function isVowel(char) {
    return ALL_VOWELS.includes(char);
}
function isSeparator(char) {
    return SEPARATORS.includes(char);
}

const COMMON_CONSONANT_PAIRS_DATA = Object.freeze({
    'b': new Set(['l', 'r']),
    'c': new Set(['h', 'k', 'l', 'r']),
    'd': new Set(['r']),
    'f': new Set(['l', 'r']),
    'g': new Set(['g', 'h', 'l', 'r']),
    'k': new Set(['n']),
    'l': new Set(['l', 't']),
    'm': new Set(['m', 'n']),
    'n': new Set(['n', 'g']),
    'p': new Set(['p', 'h', 'l', 'r', 's']),
    'q': new Set(['u']),
    'r': new Set(['h', 'r']),
    's': new Set(['c', 'h', 'k', 'l', 'm', 'n', 'p', 's', 't', 'w']),
    't': new Set(['h', 'r', 'w']),
    'w': new Set(['h', 'r']),
});
const EXTENDED_CONSONANT_PAIRS_DATA = Object.freeze({
    'c': new Set(['s', 'z']),
    'd': new Set(['d', 'n', 'w', 'z']),
    'h': new Set(['m', 'n']),
    'k': new Set(['h', 'k', 's', 'v']),
    'l': new Set(['f', 'j']),
    'n': new Set(['t', 'h', 'k']),
    'p': new Set(['t']),
    'r': new Set(['n', 'z']),
    'v': new Set(['s', 'k']),
});

function randomPairedCharFromConsonant(rng, rhs) {
    var keys = Array.from( COMMON_CONSONANT_PAIRS_DATA[rhs] );
    var randomEntry = rng.range( keys.length - 1 )
    return keys[ randomEntry ];
};

function validEnglishConsonantPair(lhs, rhs) {
    if (isSeparator(lhs) || isSeparator(rhs)) {
        return true;
    }
    const allowedRhsChars = COMMON_CONSONANT_PAIRS_DATA[lhs];
    return allowedRhsChars?.has(rhs) || false;
}
function validExtendedConsonantPair(lhs, rhs) {
    if (isSeparator(lhs) || isSeparator(rhs)) {
        return true;
    }
    const allowedRhsChars = EXTENDED_CONSONANT_PAIRS_DATA[lhs];
    return allowedRhsChars?.has(rhs) || false;
}

const BREAK_SEPARATORS = Object.freeze([' ', ' ', ' ', '\'', '-', '-']);

function randomBreak(rng) {
    var randomEntry = rng.range( BREAK_SEPARATORS.length - 1 )
    return BREAK_SEPARATORS[ randomEntry ];
}

// ------------------------------------------------------------------------------------------------

class TrigramAssembler {

    /** @type {string} */
    s;

    // Private constructor, use static factory methods.
    /**
     * @param {string} initialContent
     * @param {boolean} isFromRootChars - Special handling for the 3-char root constructor
     */
    constructor(initialContent, isFromRootChars = false) {
        if (isFromRootChars) {
            if (initialContent === null || initialContent === undefined) {
                const msg = "TrigramAssembler (root_chars): root_chars cannot be null or undefined.";
                console.error(msg);
                throw new Error(msg);
            }
            if (initialContent.length < 3) {
                const msg = `TrigramAssembler (root_chars): root_chars length is ${initialContent.length}, expected at least 3.`;
                console.error(msg);
                throw new Error(msg);
            }
            this.s = initialContent.substring(0, 3);
        } else {
            if (initialContent === null || initialContent === undefined) {
                 const msg = "TrigramAssembler (fromString/empty): initialContent cannot be null or undefined.";
                 console.error(msg);
                 throw new Error(msg);
            }
            this.s = initialContent;
        }
    }

    /**
     * Creates an assembler from 3 root characters.
     * @param {string} root_chars - Expected to be a string of at least 3 characters.
     * @returns {TrigramAssembler}
     */
    static fromRootChars(root_chars) {
        return new TrigramAssembler(root_chars, true);
    }

    /**
     * Creates an assembler from a given string.
     * @param {string} from_string
     * @returns {TrigramAssembler}
     */
    static fromString(from_string) {
        return new TrigramAssembler(from_string, false);
    }

    /**
     * Creates a new assembler with an empty string.
     * @returns {TrigramAssembler}
     */
    static newEmptyAssembler() {
        return new TrigramAssembler("", false);
    }

    /**
     * Gets the current length of the assembled string.
     * @returns {number}
     */
    getSize() {
        return this.s.length;
    }

    /**
     * Gets the character at a specific index.
     * @param {number} idx
     * @returns {string} The character at the index, or throws if out of bounds.
     */
    at(idx) {
        if (idx < 0 || idx >= this.s.length) {
            const msg = `TrigramAssembler.at: Index ${idx} out of bounds for string of length ${this.s.length}.`;
            console.error(msg);
            throw new RangeError(msg);
        }
        return this.s[idx];
    }

    /**
     * Appends the string content of another TrigramAssembler.
     * @param {TrigramAssembler} other
     */
    merge(other) {
        if (!(other instanceof TrigramAssembler)) {
            console.error("TrigramAssembler.merge: 'other' must be an instance of TrigramAssembler.");
            return; // Or throw
        }
        this.appendString(other.asString());
    }

    /**
     * Appends a string.
     * @param {string} to_append
     */
    appendString(to_append) {
        if (typeof to_append !== 'string') {
            console.error("TrigramAssembler.appendString: input must be a string.");
            return;
        }
        this.s += to_append;
    }

    /**
     * Appends a single character.
     * @param {string} to_append_char - Expected to be a single character string.
     */
    appendChar(to_append_char) {
        if (typeof to_append_char !== 'string' || to_append_char.length !== 1) {
            console.error("TrigramAssembler.appendChar: input must be a single character string.");
            return;
        }
        this.s += to_append_char;
    }

    /**
     * Prepends a single character.
     * @param {string} to_prepend_char - Expected to be a single character string.
     */
    prependChar(to_prepend_char) {
        if (typeof to_prepend_char !== 'string' || to_prepend_char.length !== 1) {
            console.error("TrigramAssembler.prependChar: input must be a single character string.");
            return;
        }
        this.s = to_prepend_char + this.s;
    }

    /**
     * Returns the current string.
     * @returns {string}
     */
    asString() {
        return this.s;
    }

    /**
     * Injects a string into the given index
     */
    spliceAtNearestVowel(start_index, splice_string) {

        let si = start_index
        for (; si < this.getSize(); si++) {
            if ( isVowel(this.at(si)) )
                break;
        }
        si ++;
        if ( si < this.getSize() - 1 ) {
            this.s = this.s.slice(0, si) + splice_string + this.s.slice(si);
        }
    }

    /**
     * Converts the last three characters of the string to a U32 value.
     * The C++ packing is: char1 | (char2 << 8) | (char3 << 16)
     * where char1 is (string_len - 3), char2 is (string_len - 2), char3 is (string_len - 1).
     * @returns {number}
     */
    asU32() {
        const currentString = this.s;
        const string_len = currentString.length;

        if (string_len < 3) {
            const msg = `TrigramAssembler.asU32: String length is ${string_len}, requires at least 3 characters.`;
            console.error(msg);
            throw new Error(msg); // Mimic C++ assert failure
        }

        const char1_code = currentString.charCodeAt(string_len - 3); // Last third char
        const char2_code = currentString.charCodeAt(string_len - 2); // Last second char
        const char3_code = currentString.charCodeAt(string_len - 1); // Last char

        // Ensure codes are treated as bytes for packing
        const trigramU32 = (char1_code & 0xFF) |
                           ((char2_code & 0xFF) << 8) |
                           ((char3_code & 0xFF) << 16);
        
        // JavaScript bitwise operations result in a signed 32-bit integer.
        // For character codes (0-255), the sum won't exceed 0xFFFFFF (24 bits),
        // so it will remain positive and correctly represent the uint32_t value.
        // If an unsigned 32-bit number is strictly needed for later JS bitwise ops,
        // one might use `trigramU32 >>> 0`.
        return trigramU32 >>> 0;
    }
}

/**
 * Pads unwelcome consonant clusters in a TrigramAssembler's string with random vowels.
 *
 * @param {object} rng - A pseudo-random number generator instance 
 * @param {TrigramAssembler} inputAssembler - The input TrigramAssembler instance containing the original string
 * @param {boolean} interpretYAsVowel - If true, 'y' is treated as a vowel for vowel checks
 * @param {boolean} allowExtendedRules - If true, uses the extended set of valid consonant pairs in addition to the default set
 * @returns {TrigramAssembler} A new TrigramAssembler instance with consonant clusters potentially padded
 */
function padInvalidConsonantClusters(rng, inputAssembler, interpretYAsVowel, allowExtendedRules) {
    const result = TrigramAssembler.newEmptyAssembler();

    let lastLetterWasConsonant = false;
    let lastLetterProcessed = '';

    const inputSize = inputAssembler.getSize();
    for (let i = 0; i < inputSize; i++) {
        const originalCurrentLetter = inputAssembler.at(i);
        // normalize current letter to lowercase
        const currentLetterLower = originalCurrentLetter.toLowerCase();

        const isCurrentLetterVowel = isVowel(currentLetterLower);

        if (!isCurrentLetterVowel) { // Current letter is a consonant
            // Check for invalid consonant pairing if the previous letter was also a consonant.
            // The validEnglishConsonantPair and validExtendedConsonantPair functions
            // already handle separators correctly (returning true if a separator is involved).
            // If lastLetterProcessed is '', pair checks will correctly yield false.
            const isValidDefaultPair = validEnglishConsonantPair(lastLetterProcessed, currentLetterLower);
            const isValidExtendedPair = allowExtendedRules && validExtendedConsonantPair(lastLetterProcessed, currentLetterLower);

            if (lastLetterWasConsonant && !isValidDefaultPair && !isValidExtendedPair) {
                
                // Optionally insert one of the valid consonant right-hand-sides before we then pad with a vowel
                // .. this usually flows okay and adds some variety
                if ( rng.range(100) > 50 )
                    result.appendChar(randomPairedCharFromConsonant(rng, lastLetterProcessed));

                // pop in a vowel to diffuse the uncommon consonant pairing strangeness
                result.appendChar(chooseRandomVowel(rng, interpretYAsVowel));
            }
            lastLetterWasConsonant = true;
        } else { // Current letter is a vowel
            lastLetterWasConsonant = false;
        }

        // Store the lowercase version of the current letter for the next iteration's checks.
        lastLetterProcessed = currentLetterLower;

        // Append the original character (preserving its case) to the result.
        result.appendChar(originalCurrentLetter);
    }

    // Fix up cases where we have a word starting with two identical consonants, eg `kkirino`
    // This isn't necessarily wrong but it often doesn't pronounce well
    if ( result.at(0) == result.at(1) ) {
        if ( !isVowel( result.at(0) ) ) {
            result.prependChar(chooseRandomVowel(rng, false));
        }
    }
    // .. And same for the final two characters
    let lastCharacter = result.getSize() - 1;
    if ( lastCharacter >= 1 ) {
        if ( result.at(lastCharacter) == result.at(lastCharacter - 1) ) {
            if ( !isVowel( result.at(lastCharacter) ) ) {
                result.appendChar(chooseRandomVowel(rng, false));
            }
        }
    }

    return result;
}