// included by generated code; tidy up after including tables

// ------------------------------------------------------------------------------------------------
// turn off any changes made in common-all-begin
//

#if defined(MKV_DISABLED_MSVC_OPT)
#pragma optimize( "", on )
#endif

#undef MKV_DISABLE_OPT
#undef MKV_DATA

// ------------------------------------------------------------------------------------------------
// use a recursive macro call to define switch/case code for each available namespace choice in the
// generated code - MKV_CHOICE_LIST is written automatically into mk-all during generation
//
// this then lets us have a generic set of functions that can take an enum choice to select a
// namespace rather than having to address them directly
//

#define MKV_DECLARE_SRR_CASE( _ns ) \
    case Choice::_ns:               \
        return _ns::BeginGeneration( input_user_random_u32 );

#define MKV_DECLARE_SNL_CASE( _ns ) \
    case Choice::_ns: return _ns::SelectNextLetter( trigram_u32, input_user_weight, input_user_random_u32, decision_fn );

namespace mk {

inline TrigramAssembler
BeginGeneration( const Choice ns_choice, const uint32_t input_user_random_u32 )
{
    switch( ns_choice ) {
        MKV_CHOICE_LIST( MKV_DECLARE_SRR_CASE )
    }

    // the switch defaults to a \0 if no matches found
    assert( 0 );
    return TrigramAssembler( "###" );
}

inline char
SelectNextLetter(
    const Choice                 ns_choice,
    const uint32_t               trigram_u32,
    const float                  input_user_weight,
    const uint32_t               input_user_random_u32,
    const BranchDecisionFunction decision_fn )
{
    switch( ns_choice ) {
        MKV_CHOICE_LIST( MKV_DECLARE_SNL_CASE )
    }

    // the switch defaults to a \0 if no matches found
    assert( 0 );
    return '#';
}

}    // namespace mk
