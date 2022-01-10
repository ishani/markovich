// generated by markovich:tablegen
// ishani.org 2021

namespace mk {
namespace england {

enum { eTrigramRoots = 2448 };

static const char g_trigramRoots[ (eTrigramRoots * 3) + 1 ] = 
    "abbabdabeabiaboabrabsabuaccaceachackacoacradaadbaddadeadfadgadhadiadladmadnadoadradsadwadyaffaftagbagdageaggaghagiaglagn"
    "agpagragsahaaidaigailainairaisaitakeakhaksalaalbalcaldalealfalgalhalialkallalmalnaloalpalralsaltalualvalwamaambameamfamh"
    "amiammamoampamsanaanbancandaneanfanganhaniankanlannanoanpansantanvanwapcapeaphaplappapsaptapwaraarbarcardarearfargarhari"
    "arkarlarmarnaroarparrarsartarvarwaryasaasbascaseashasiaskaslasoaspassastaswatbatcateatfathatiatlatmatoatratsattatwaubauc"
    "audaugaulaunaurausautauxavaaveaviawaawbawcawdaweawkawlawnawsawtaxeaxhaxlaxmaxtaybayeayfayhaylaymaynaysaytaywazaazebabbac"
    "badbagbalbambanbarbasbatbaubavbawbaybbabbebbibeabebbecbedbeebegbelbembenberbesbetbevbewbexbeybicbidbigbilbinbirbisbitbla"
    "bleblibloblublybneboabocbodbogbohbolbonbooborbosbotboubowboxboybrabrebribrobrubrybshbudbugbulbunburbusbutbuxbyfcabcadcai"
    "calcamcancapcarcascatcaucawccaccoceacebcefcehcelcemcencetchachbchdchechichlchmchochuchwchycinckackbckcckdckeckfckhcklckm"
    "cknckockrcksckwclacleclicloclucoacobcodcogcolcomconcoocopcorcoscotcoucowcoxcracrecricrocrucrycubcudculcumcupcurcuscutcux"
    "dacdaddagdaldamdandardaudavdawdaydbadbedbodbrdcoddaddeddiddoddydeadebdecdeddeedeldemdendepderdesdetdevdewdfadgadgedgidgr"
    "dgwdhadhedhodhudiadicdiddigdildimdindipdisditdladledlidlodmadmedmidmodnadnednodobdocdoddogdoldomdondordoudowdoxdpodradre"
    "dridrodrudrydsadsbdsedshdsidsodspdstdswdtodubducdudduldumdundurdutdwadwedwidymeabeaceadeafeageaheakealeameaneapeareaseat"
    "eaueaveawebaebbebdebeebieboebrebsebuecaeccecheckecoedaedbedceddedeedgedhediedledmednedoedredsedweebeeceedeegeeheekeeleen"
    "eepeereeseeteffefoegaegbegeeggegieglegoegregseguehaeheehiehoeigeineireisekeekielaelbeldeleelfelgelhelielkellelmeloelpels"
    "eltelvelwemaembemeemiemmemoempemsenaenbencendeneenfengenhenienkenlenmennenoenpenrensentenwenyeobeoleoneopepaepcepdepeeph"
    "epiepoeppepseptepwequeraerbercerdereerfergerherierkerlermerneroerperrerserterverweryesaesbescesdeseesfesgeshesieskeslesm"
    "esoespessesteswetbethetietletretsettetwevaeveevievoewaewbewcewdeweewfewhewiewkewlewnewoewsewtewyexbextexweybeyceyeeyheyl"
    "eymeyneyreyseyteywezaezefacfaifalfanfarfaufawfcofelfenferfetffcffeffifflffoffrfilfinfirfitflaflefliflofolfonforfosfoufow"
    "foxfrafrefrifrofryfulfurgabgadgaigalgamgangargasgatgaugawgaygbagbegbrgeagebgedgehgelgemgengergesgewggaggbggeghaghbgheghi"
    "ghoghsghtghwgibgidgilginglaglegliglogmognagnegobgodgolgongoogorgosgotgowgragregrigrogrugsbgsdgsegshgslgstgswgthgtoguegui"
    "gulgumgungurgusguygwagwegwigwohabhachadhaghaihalhamhanhapharhashathauhavhawhaxhayhazhbehbohcoheahebhedheehegheihelhemhen"
    "hepherheshethevhewhexheyhfohiahidhiehighilhimhinhiphirhishithlahlehlohmehmohoahobhochodhogholhomhonhoohophorhoshothouhow"
    "hpohrahrehrihrohruhsthtohtwhudhughulhumhunhurhushuthuxhwahwohydhylhynhytiamianiaribbibsicaiceichickicoidaidbiddideidgidl"
    "idmidnidsidwielieriffiftigbiggighigligmignigsigwikeilailbilcildileilfilkillilmilniloilpilsiltilvilwimbimeimmimoimpimsina"
    "inbincindineinfinginhiniinkinminninoinsintinwinxipeiplippipsiptirbirdireirkirlirmirrirsirtirwisbiscisdiseishiskislispiss"
    "istiswitaitbitciteithitlitmitoitsittitwitziveiviivoixbixoizeizzjerjorjoykamkbekbokeakedkeekefkegkehkeikelkemkenkerkesket"
    "kewkeykfokhakhokidkilkimkinkirkitklaklekmoknaknekniknoknukpokroksbkshksokspkstkswkwakwekwikwokynlablacladlaglailamlanlap"
    "larlaslatlavlawlaxlaylazlbalbelbolbrlcalchlcoldbldcldeldfldhldildmldoldrldsldwlealeblecledleelefleglehleilemlenleolepler"
    "lesletlevlewlexleylezlfalfolfrlgalgrlhalholialibliclidlielifliglillimlinliplislitlivlixlkelkhlkslkwllallbllcllellfllgllh"
    "llillmllollsllwllylmalmelmilmolmslnelnhlniloaloblodloglomlonlooloplorloslotloulovlowloxlpelphlpolrelrilrolsalsblsdlselsh"
    "lsilsllsolstlswltbltcltelthltiltmltoltrltwlublucludluglullumlunluplurluslutluxlvalvelvilwalwelwilyblydlyflymlynlyplytlyw"
    "mabmacmadmaemagmaimalmanmapmarmasmatmaumawmaxmaymbemblmbombrmeamedmeemelmenmeomermesmetmewmeymhamidmilminmismitmixmlemme"
    "mmimmomobmodmogmolmonmoomormosmotmoumowmpempfmpimplmpompsmptmromsamsbmsdmsgmshmslmstmudmulmunmurmusmutmytnabnacnadnagnai"
    "nalnannapnarnasnatnaunbanbenbonbrncancenchnclnconcrndandbndendgndhndindlndmndondpndrndsndtndwndyneanebnecnedneenegnehnei"
    "nelnennepnernesnetnewneynfangangbngcngdngengfnghnginglngmngongrngsngtngungwnhanhenhonhunibnicnienignilnimninnionisnitnje"
    "nkbnkenkhnkinklnksnlanlenlinlonmanmenmonnannenninnonnsnnynoanobnodnolnonnoonornosnotnounownpinponrinronsansbnscnsdnsensg"
    "nshnsinslnsonspnstnswntantcntenthntintlntmntnntontrntsntwnunnupnutnvenvinwanwenwinwonyanycnyenymnytoadoakoaloanoaroasoat"
    "obbobeobhobioboobsobuoccochockodaodbodcoddodeodfodgodhodiodlodmodoodpodrodsodwodyoffoftogaogdogeoggoghogloguokeokhoksola"
    "olbolcoldoleolfolgolholiolkollolmolnoloolpolsoltolvolwolyombomeomhommompomsonaonboncondoneonfongonhonionkonmonnonoonsont"
    "onvonwonyooboodookooloomoonooroosootopeoploppopsoptopworaorborcordoreorforgorhoriorkorlormornoroorporrorsortorvorwosbosc"
    "oseosgoslosmospossostoswotaotboteothotlotmotsottotwoucoudoulounourousoutovaoveowaowbowcowdoweowgowhowiowlowmownowpowsowt"
    "oxboxcoxdoxeoxhoxloxtoxwoyloynoytozepacpadpagpaipalpampanpapparpaspatpawpaypchpeapebpedpeepegpelpenpeoperpespetpewphaphe"
    "phiphopicpidpiepigpilpimpinpippispitpixplapleploplupnapnepodpolponpoopopporpospotpoupowpoyppappeppippopraprepriproprupsb"
    "pshpstpswpthptiptopulpunpurputpuxpwapwepyepyrquaquequiquorabracradrafragrairalramranraprasratrauravrawrayrazrbarberbirbl"
    "rborbrrcarcerchrclrcordardbrderdhrdirdlrdordrrdsrdwrearebrecredreerefregrehreirelremrenreprerresretrevrewreyrforgargergh"
    "rgirgorgrrharherhirhorhurhyriaribricridrierifrigrilrimrinrioriprisritrivrixrizrkbrkerkhrklrksrkwrlarlbrlcrldrlerlirlorls"
    "rmarmbrmermirmormsrnarnbrncrndrnernfrnhrnirnlrnornsrntrnwroarobrocrodroerofrogrolromronrooroprosrotrourowroxroyrparperpo"
    "rpsrptrrarrerrirrorrsrryrsarsbrsdrsersgrshrsirslrsorsprstrswrtbrterthrtirtlrtmrtortrrtsrtwruarubrucrudruerugruirulrumrun"
    "rurrusrutrvarvervirwarwerwiryarybrydryeryhrynrysrytrzesabsacsadsalsamsansapsarsatsausawsaxsbasbesboscascesclscoscrscusda"
    "sdeseasebsecsedseesehseiselsemsensersetsewsfosgrshashbshcsheshishlshmshoshpshrshushwsibsidsigsilsimsinsissitsixskaskeski"
    "slasleslisloslysmasmesmismosnasnesnisnosodsolsomsonsopsorsotsousowspaspespisposprspussassbsscssessgssissostastbstcstdste"
    "sthstistlstmstnstostrstustwstysubsucsudsugsulsunsursussutsveswasweswiswosydtactadtagtaitaltamtantaptartastattavtawtbotbr"
    "tchtcltcoteatebtectedteeteftegtehteltemtenteptertestettewtfotgatgrthathbthcthdthethfthgthithlthmthnthothrthsthuthwthytib"
    "tictidtiltimtintiptirtistittivtixtlatletlitlotmatmetmotnatnetnotoatobtodtoktoltomtontootoptortostottoutowtoxtratretritro"
    "trutrytsbtsetsftsgtshtsltsmtsotstttattettittottsttytubtudtuetuftugtunturtuttwatwetwitwotwytybtyntyrtyttywuarubbubeublubw"
    "uccuchuckudbuddudeudgudhudiudludoudsudwueruesuffugbuggughuiduiluinuisuitulbulculduleulfulgulkullulmulsultulwumbummumpums"
    "unbuncunduneungunhuniunkunnunsuntunwuphupluppupsupwurburcurdureurfurguriurlurmurnurpurrursurturvurwuryurzusbuseushusluss"
    "ustutbutcuthutlutnutsuttutwuxtvadvagvalvanvarveavecvedvelvenvervesvetvicvidvilvinvisvitvolvonvosvowwadwafwaiwalwanwarwas"
    "watwaywbawbewbiwbowbrwbuwcowdeweawebwedweewelwenweowerweswetweywfowgawhawhewhiwhowhywidwigwilwinwiswitwixwkewkhwkswlawle"
    "wmawnewnhwnlwnswntwolwonwooworwouwpowrawrewriwrowsbwsewshwslwstwtewthwtowyawybwycwyewylwymwynxenxhoxtextoxwoyalyanyarybe"
    "yboybrybuychycoyddydeydoyeayelyeoyeryetyewygayhayhiykeylayleymeymoympynayndyneyngynoynsyntypoyreyriyroyseyshysoystyswyte"
    "ythytoywazanzarzebzelzle";

#include "inline/common-roots.inl"

} // namespace england
} // namespace mk