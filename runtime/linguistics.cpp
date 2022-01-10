//
// markovich 
// procedural name generation example
// harry denholm, ishani.org 2022
//


#include "pch.h"

#include "linguistics.h"
#include "pcg_basic.h"
#include <array>

char
ChooseRandomVowel( pcg32_random_t& rng, bool include_y /* = false */ )
{
    const std::array<char, 6> vowels{ { 'a', 'e', 'i', 'o', 'u', 'y' } };

    const uint32_t choice = pcg32_random_u32_range( rng, include_y ? 6 : 5 );

    return vowels[choice];
}

// https://en.wikipedia.org/wiki/List_of_Latin-script_digraphs
// https://www.enchantedlearning.com/consonantblends/index.shtml

bool ValidEnglishConsonantPair( const char lhs, const char rhs )
{
    // allow all run-ons with separator letters like "-" or "'"
    if ( IsSeparator( lhs ) || IsSeparator( rhs ) )
        return true;

    switch ( lhs )
    {
    case 'b': return (
        rhs == 'l' ||
        rhs == 'r');
    case 'c': return (
        rhs == 'h' ||
        rhs == 'k' ||
        rhs == 'l' ||
        rhs == 'r' );
    case 'd': return (
        rhs == 'r');
    case 'f': return (
        rhs == 'l' ||
        rhs == 'r');
    case 'g': return (
        rhs == 'g' ||
        rhs == 'h' ||
        rhs == 'l' ||
        rhs == 'r');
    case 'k': return (
        rhs == 'n');
    case 'l': return (
        rhs == 'l');
    case 'm': return (
        rhs == 'm' ||
        rhs == 'n');
    case 'n': return (
        rhs == 'n' ||
        rhs == 'g');
    case 'p': return (
        rhs == 'p' ||
        rhs == 'h' ||
        rhs == 'l' ||
        rhs == 'r' ||
        rhs == 's');
    case 'q': return (
        rhs == 'u');
    case 'r': return (
        rhs == 'h' ||
        rhs == 'r');
    case 's': return (
        rhs == 'c' ||
        rhs == 'h' ||
        rhs == 'k' ||
        rhs == 'l' ||
        rhs == 'm' ||
        rhs == 'n' ||
        rhs == 'p' ||
        rhs == 't' ||
        rhs == 's' ||
        rhs == 'w');
    case 't': return (
        rhs == 'h' ||
        rhs == 'r' ||
        rhs == 'w');
    case 'w': return (
        rhs == 'h' ||
        rhs == 'r');

    default:
        return false;
    }
}

bool ValidExtendedConsonantPair( const char lhs, const char rhs )
{
    // allow all run-ons with separator letters like "-" or "'"
    if ( IsSeparator( lhs ) || IsSeparator( rhs ) )
        return true;

    switch ( lhs )
    {
    case 'c': return (
        rhs == 's' ||
        rhs == 'z');
    case 'd': return (
        rhs == 'd' ||
        rhs == 'n' ||
        rhs == 'w' ||
        rhs == 'z');
    case 'h': return (
        rhs == 'm' ||
        rhs == 'n');
    case 'k': return (
        rhs == 'h' ||
        rhs == 'k' ||
        rhs == 's' ||
        rhs == 'v');
    case 'l': return (
        rhs == 'f' ||
        rhs == 'j');
    case 'n': return (
        rhs == 't' ||
        rhs == 'h' ||
        rhs == 'k' );
    case 'p': return (
        rhs == 't');
    case 'r': return (
        rhs == 'n' ||
        rhs == 'z');
    case 'v': return (
        rhs == 's' ||
        rhs == 'k');

    default:
        return false;
    }
}

mk::TrigramAssembler PadInvalidConsonantClusters( pcg32_random_t& rng, const mk::TrigramAssembler& input, const bool considerAdditionalVowels, const bool allowExtendedRules )
{
    mk::TrigramAssembler result = mk::TrigramAssembler::NewEmptyAssembler();

    bool lastLetterWasConsonant = false;
    char lastLetter = 0;

    for ( auto i = 0; i < input.GetSize(); i++ )
    {
        const char thisLetter = input.At( i );
        const bool isVowel = IsVowel( thisLetter, considerAdditionalVowels );

        if ( !isVowel )
        { 
            const bool isValidDefaultPair   = ValidEnglishConsonantPair( lastLetter, thisLetter );
            const bool isValidExtendedPair  = allowExtendedRules && ValidExtendedConsonantPair( lastLetter, thisLetter );

            if ( lastLetterWasConsonant &&
                !isValidDefaultPair &&
                !isValidExtendedPair )
            {
                result.AppendChar( ChooseRandomVowel( rng, considerAdditionalVowels ) );
            }

            lastLetterWasConsonant = true;
        }
        else
        {
            lastLetterWasConsonant = false;
        }

        lastLetter = thisLetter;
        result.AppendChar( thisLetter );
    }

    return result;
}

mk::TrigramAssembler LimitSeparators( const mk::TrigramAssembler& input )
{
    mk::TrigramAssembler result = mk::TrigramAssembler::NewEmptyAssembler();

    bool lastLetterWasSeparator = false;

    for ( auto i = 0; i < input.GetSize(); i++ )
    {
        const char thisLetter = input.At( i );
        const bool isSeparator = IsSeparator( thisLetter );

        if ( isSeparator )
        {
            if ( lastLetterWasSeparator )
                continue;

            lastLetterWasSeparator = true;

            if ( i == 0 || i == input.GetSize() - 1 )
                continue;
        }
        else
        {
            lastLetterWasSeparator = false;
        }

        result.AppendChar( thisLetter );
    }

    return result;
}

bool HasSingleFollowingSeparator( const mk::TrigramAssembler& input )
{
    if ( input.GetSize() < 2 )
        return false;

    return IsSeparator( input.At( input.GetSize() - 2 ) );
}
