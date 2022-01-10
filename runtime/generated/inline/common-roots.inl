// included by generated code; define any shared code for each namespace here

inline TrigramAssembler BeginGeneration( const uint32_t input_user_random_u32 )
{
    const uint32_t chosen_index = ( input_user_random_u32 % eTrigramRoots );
    return TrigramAssembler( &g_trigramRoots[chosen_index * 3] );
}
