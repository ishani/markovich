//
// markovich 
// procedural name generation example
// harry denholm, ishani.org 2022
//

#include "pch.h"
#include "linguistics.h"

namespace mk {
#define MK_CHOICE(_var) Choice::_var,
    static const std::vector< Choice > AllThemeChoices{
            MKV_CHOICE_LIST( MK_CHOICE )
    };
#undef MK_CHOICE
} // namespace mk


#define MK_CHOICE( _ns ) \
    case mk::Choice::_ns: return #_ns;

static std::string to_string( const mk::Choice& ns_choice ) {
    switch ( ns_choice ) {
        MKV_CHOICE_LIST( MK_CHOICE )
    }
    return "unknown";
}
#undef MK_CHOICE


namespace decision_functions {

static char WeightThreshold(
    const char*     data_table_chars,
    const uint16_t* data_table_weights_u16,
    const size_t    data_table_size,
    const float     input_weight,
    const uint32_t  input_seed )
{
    const uint16_t target_weight  = (uint16_t) roundf( input_weight * 0x00010000 );
    uint16_t       current_weight = 0;
    size_t         data_index     = 0;

    for( ; data_index < data_table_size; data_index++ )
    {
        current_weight += data_table_weights_u16[data_index];
        if( current_weight >= target_weight )
        {
            return data_table_chars[data_index];
        }
    }

    return data_table_chars[data_table_size - 1];
}

static char Random(
    const char*     data_table_chars,
    const uint16_t* data_table_weights_u16,
    const size_t    data_table_size,
    const float     input_weight,
    const uint32_t  input_seed )
{
    const size_t random_index = ( size_t )( input_seed % data_table_size );

    return data_table_chars[random_index];
}

}    // namespace decision_functions

void padRight( std::string& subject, int32_t toLength )
{
  if ( toLength > subject.size() )
    subject.insert( subject.size(), toLength - subject.size(), ' ');
}


#ifdef MK_MINI_DEMO

// ---------------------------------------------------------------------------------------------------------------------

const char* getModelName( mk::Choice choice )
{
#define MKV_NAME( _entry )  case mk::Choice::_entry: return #_entry;
    switch ( choice )
    {
      MKV_CHOICE_LIST( MKV_NAME )
    }
    return "unknown";
}

int main( int argv, char** argc )
{
    auto rng = pcg32_seed( std::time( nullptr ), 17322130906412408941ULL );

    const mk::Choice randomModel = (mk::Choice)pcg32_random_u32_range( rng, 7 );
    printf( "using [%s] ...\n", getModelName( randomModel ) );

    for ( uint32_t word = 0; word < 16; word++ )
    {
        const uint32_t initialSeed = pcg32_random_u32( rng );

        auto assembler = mk::BeginGeneration( randomModel, initialSeed );
        const uint32_t wordLength = 3 + pcg32_random_u32_range( rng, 5 );

        float randomWeight = pcg32_random_float( rng );

        for ( uint32_t count = 0; count < wordLength; count ++ )
        {
            const uint32_t randomChoice = pcg32_random_u32( rng );

            char nextChar = mk::SelectNextLetter(
                randomModel,
                assembler.AsU32(),
                randomWeight,
                randomChoice,
                &decision_functions::WeightThreshold );

            assembler.AppendChar( nextChar );

            randomWeight *= 0.8f;
        }

        assembler = PadInvalidConsonantClusters( rng, assembler, true, false );
        assembler = LimitSeparators( assembler );

        printf( "%s\n", assembler.AsString().c_str() );
    }
}


#else // MK_MINI_DEMO

// ---------------------------------------------------------------------------------------------------------------------

#include <chaiscript/extras/math.hpp>
#include <chaiscript/extras/string_methods.hpp>


int main( int argv, char** argc )
{
    printf( "Markovich | Procedural Name Generator | ishani.org 2022\n" );

    chaiscript::ChaiScript chai;
    {
        auto mathlib = chaiscript::extras::math::bootstrap();
        chai.add( mathlib );
    }
    {
        auto stringlib = chaiscript::extras::string_methods::bootstrap();
        stringlib->add( chaiscript::fun( padRight ), "padRight" );
        chai.add( stringlib );
    }

    // register rng
    chai.add( chaiscript::user_type<pcg32_random_t>(),          "RandomState" );
    chai.add( chaiscript::fun( &pcg32_seed ),                   "CreateRNG" );
    chai.add( chaiscript::fun( []()
        { 
            return pcg32_seed( std::time( nullptr ), 17322130906412408941ULL ); 
        }),                                                     "CreateRNGNonDeterministic" );
    chai.add( chaiscript::fun( &pcg32_random_u32 ),             "GetRandom" );
    chai.add( chaiscript::fun( &pcg32_random_u32_range ),       "GetRandomInRange" );
    chai.add( chaiscript::fun( &pcg32_random_float ),           "GetRandomFloat" );
    

    chai.add( chaiscript::fun( &mk::BeginGeneration ),          "BeginGeneration" );
    chai.add( chaiscript::fun( []( 
        mk::TrigramAssembler&             current_string,
        const mk::Choice                  ns_choice,
        const float                       input_user_weight,
        const uint32_t                    input_user_random_u32,
        const mk::BranchDecisionFunction& decision_fn )
        { 
            const auto nextChar = mk::SelectNextLetter(
                ns_choice,
                current_string.AsU32(),
                input_user_weight,
                input_user_random_u32,
                decision_fn );

            if ( nextChar == 0 )
                return false;

            current_string.AppendChar( nextChar );
            return true;
        }),                                                     "AddLetter" );

    chai.add( chaiscript::vector_conversion<std::vector<mk::Choice>>() );
    chai.add( chaiscript::fun( []( 
        mk::TrigramAssembler&             current_string,
        const std::vector<mk::Choice>&    ns_choice,
        const float                       input_user_weight,
        const uint32_t                    input_user_random_u32,
        const mk::BranchDecisionFunction& decision_fn )
        { 
            char nextChar = 0;
            
            size_t choiceIndex = 0;
            const size_t choiceCount = ns_choice.size();

            while ( nextChar == 0 )
            {
                if ( choiceIndex >= choiceCount )
                    return false;

                nextChar = mk::SelectNextLetter(
                    ns_choice[choiceIndex],
                    current_string.AsU32(),
                    input_user_weight,
                    input_user_random_u32,
                    decision_fn );

                choiceIndex++;
            }

            current_string.AppendChar( nextChar );
            return true;
        }),                                                     "AddLetter" );

    chai.add( chaiscript::fun( []( 
        mk::TrigramAssembler&             current_string,
        const uint32_t                    input_user_random_u32 )
        { 
            for ( const auto choice : mk::AllThemeChoices )
            {
                const auto nextChar = mk::SelectNextLetter(
                    choice,
                    current_string.AsU32(),
                    0.0f,
                    input_user_random_u32,
                    decision_functions::Random );

                if ( nextChar != 0 )
                {
                    current_string.AppendChar( nextChar );
                    return true;
                }
            }

            return false;
        }),                                                     "TryAddAnyLetter" );


    chai.add( chaiscript::fun( &PadInvalidConsonantClusters ),  "PadInvalidConsonantClusters" );
    chai.add( chaiscript::fun( &LimitSeparators ),              "LimitSeparators" );
    chai.add( chaiscript::fun( &HasSingleFollowingSeparator ),  "HasSingleFollowingSeparator" );

    
    chai.add( chaiscript::fun( &decision_functions::WeightThreshold ),  "FnWeightThreshold" );
    chai.add( chaiscript::fun( &decision_functions::Random ),           "FnRandom"          );

    chai.add( chaiscript::user_type<mk::TrigramAssembler>(),            "TrigramAssembler"  );
    chai.add( chaiscript::constructor<mk::TrigramAssembler( const mk::TrigramAssembler& )>(), "TrigramAssembler" );
    chai.add( chaiscript::fun( []( mk::TrigramAssembler& u, const mk::TrigramAssembler& v ) { u = v; } ), "=" );
    chai.add( chaiscript::fun( &mk::TrigramAssembler::AsString ),       "AsString"          );
    chai.add( chaiscript::fun( &mk::TrigramAssembler::Merge ),          "Merge"             );
    chai.add( chaiscript::fun( &mk::TrigramAssembler::AppendChar ),     "AppendChar"        );
    chai.add( chaiscript::fun( &mk::TrigramAssembler::PrependChar ),    "PrependChar"       );

    // mk::Choice to_string overload
    chai.add( chaiscript::fun( &to_string ),                            "to_string"       );

    // mk::Choice value exposure
#define MK_CHOICE(_var) {mk::Choice::_var, #_var},

    chaiscript::ModulePtr m = chaiscript::ModulePtr( new chaiscript::Module() );
    chaiscript::utility::add_class<mk::Choice>( *m,
        "Choice",
        {
            MKV_CHOICE_LIST( MK_CHOICE )
        });
    chai.add( m );

#undef MK_CHOICE


    try 
    {
        const auto defaultDemoScript = "../../../demo.chai";

        const char* fileToRun = nullptr;

        if ( argv <= 1 && std::filesystem::exists( defaultDemoScript ) )
            fileToRun = defaultDemoScript;
        else
            fileToRun = argc[1];

        if ( fileToRun == nullptr )
        {
            printf( "No script file provided\n" );
        }
        else
        {
            printf( "Running: %s\n", fileToRun );
            chai.eval_file( fileToRun );
        }
    }
    catch ( const chaiscript::exception::eval_error& e ) 
    {
        printf( "ERROR:\n%s\n\n----------------------------------------------\n\n%s\n", e.pretty_print().c_str(), e.what() );
    }

    return 0;
}

#endif // MK_MINI_DEMO
