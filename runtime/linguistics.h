//
// markovich 
// procedural name generation example
// harry denholm, ishani.org 2022
//

#pragma once

struct pcg_state_setseq_64;

inline bool
IsVowel(
    const char letter, bool include_y = false )
{
    switch( letter ) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            return true;
    }
    if( include_y && letter == 'y' )
        return true;

    return false;
}

inline bool
IsSeparator(
    const char letter )
{
    switch ( letter ) {
        case '\'':
        case '-':
            return true;
    }

    return false;
}

char
ChooseRandomVowel( pcg_state_setseq_64& rng, bool include_y = false );


// inject random vowels between any double consonants 
mk::TrigramAssembler PadInvalidConsonantClusters( pcg32_random_t& rng, const mk::TrigramAssembler& input, const bool considerAdditionalVowels, const bool allowExtendedRules );

// reduce number of separator characters, strip from prefix/suffix
mk::TrigramAssembler LimitSeparators( const mk::TrigramAssembler& input );

// does the string end with "-a" or "'v" .. perhaps we need to bulk it out
bool HasSingleFollowingSeparator( const mk::TrigramAssembler& input );