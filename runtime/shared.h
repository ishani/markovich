//
// markovich 
// procedural name generation example
// harry denholm, ishani.org 2022
//

#pragma once

#include <stdint.h>
#include <array>
#include <assert.h>
#include <functional>

namespace mk {

// ------------------------------------------------------------------------------------------------
// a specialist string builder that can return the current last three letters as a U32 packed trigram
// 
class TrigramAssembler {
public:
    TrigramAssembler() = delete;

    explicit inline TrigramAssembler( const char* root_chars )
    {
        assert( root_chars != nullptr );
        assert( strlen( root_chars ) >= 3 );

        mString.fill( 0 );

        mString[0] = root_chars[0];
        mString[1] = root_chars[1];
        mString[2] = root_chars[2];
    }

    inline TrigramAssembler( const std::string& from_string )
    {
        mString.fill( 0 );
        strcpy( mString.data(), from_string.c_str() );
    }

    static TrigramAssembler NewEmptyAssembler()
    {
        return TrigramAssembler( std::move(std::string("")) );
    }

    inline size_t
    GetSize() const
    {
        return strlen( mString.data() );
    }

    inline char
    At( const size_t idx ) const
    {
        return mString[idx];
    }

    inline void 
    Merge( const TrigramAssembler& other )
    {
        AppendString( other.mString.data() );
    }

    inline void
    AppendString( const char* to_append )
    {
        assert( to_append != nullptr );
        assert( strlen( to_append ) >= 1 );
        assert( strlen( mString.data() ) + strlen( to_append ) < 64 );

        strcat( mString.data(), to_append );
    }

    inline void
    AppendChar( const char to_append )
    {
        char appendBuffer[2] = { to_append, 0 };
        assert( strlen( mString.data() ) + 1 < 64 );

        strcat( mString.data(), appendBuffer );
    }

    inline void
    PrependChar( const char to_prepend )
    {
        assert( strlen( mString.data() ) + 1 < 64 );

        for ( auto i = mString.size() - 1; i >= 1; i-- )
        {
            mString[i] = mString[i - 1];
        }
        mString[0] = to_prepend;
    }

    inline std::string
    AsString() const
    {
        return mString.data();
    }

    // take the current trailing trigram and cast it to a u32 for use in search lookups
    inline uint32_t
    AsU32() const
    {
        const auto asString = AsString();
        const size_t string_len = asString.size();
        assert( string_len >= 3 );

        const char* terminal_ptr = &( asString[string_len - 3] );

        return *(uint32_t*) terminal_ptr;
    }

private:
    std::array<char, 90> mString;
};

// ------------------------------------------------------------------------------------------------
//
using BranchDecisionFunction = std::function< char(
    const char*     /*data_table_chars*/,
    const uint16_t* /*data_table_weights_u16*/,
    const size_t    /*data_table_size*/,
    const float     /*input_weight*/,
    const uint32_t  /*input_seed*/) >;

}    // namespace mk
