// generated by markovich:tablegen
// ishani.org 2021

namespace mk {
namespace arabic {

enum { eTrigramRoots = 4323 };

static const char g_trigramRoots[ (eTrigramRoots * 3) + 1 ] = 
    "'ab'ad'aj'ak'al'am'an'ar'as'at'av'aw'ay'az'ba'bi'bu'da'di'du'ed'eh'em'er'es'ey'ez'fa'ia'id'il'im'in'is'it'iy'iz'ja'la'le"
    "'li'lu'ma'mi'mu'na'ol'ow'qu'ra're'ri'ru'ta'te'ud'ur'va'wa'ya'yu'za-al-ba-bi-ch-da-de-di-e--fa-ga-ha-ho-i--ja-ka-kh-ko-ku"
    "-lo-ma-mi-mo-mu-na-ra-sa-sh-so-ta-th-ye-zaa'aa'ba'da'ea'fa'ia'ja'la'ma'na'qa'ra'ta'ua'va'wa'ya'za-kaadaamaanaaraayab'ab-"
    "abaabbabdabeabgabhabiabjabkablabmabnaboabqabrabsabtabuabyabzacaachaciad'ad-adaadbaddadeadgadhadiadkadladmadnadoadpadqadr"
    "adsaduadyadzafaafdafeaffafgafiafjafkaflafnafoafqafrafsaftafuagaagbagdageaggaghagiagjaglagmagnagoagragsagtaguagzah'ah-aha"
    "ahbahdaheahfahgahhahiahjahkahlahmahnahoahpahqahrahsahtahuahvahwahyahzaibaidaikailaimainairaisaitaiyaj'ajaajbajdajeajgajh"
    "ajiajjajkajlajmajnajoajqajrajsajuajyajzak-akaakbakdakeakfakgakhakiakkaklakmaknakoakraksaktakuakvakyakzal'al-alaalbaldale"
    "alfalgalhalialjalkallalmalnaloalpalqalralsaltalualvalwalyalzam'am-amaambamdameamfamgamhamiamjamkamlammamnamoampamqamrams"
    "amtamuamwamyamzan'an-anaanbancandaneanfanganhanianjankanlanmannanoanpanqanransantanuanvanwanyanzaosaowapaapeapiapkaplapn"
    "apoaprapsaptapuaqaaqbaqdaqeaqhaqiaqjaqlaqmaqnaqoaqqaqraqsaqtaquaqvaqzar'ar-araarbardarearfargarhariarjarkarlarmarnaroarp"
    "arqarrarsartaruarvarwaryarzas'asaasbasdaseasfasgashasiasjaskaslasmasnasoaspasqasrassastasuasvaswasyat'ataatbateatgathati"
    "atjatkatlatmatnatoatratsattatuatvatyaulausauwav'av-avaavbavdaveavgaviavjavkavlavmavnavoavpavravsavuavvavyavzaw'awaawbawd"
    "aweawfawgawhawiawjawkawlawmawnawpawqawrawsawtawuawwawyawzay'ayaaybaydayeayfaygayhayiayjaykaylaymaynayoaypayqayraysaytayu"
    "ayvaywayyayzaz-azaazbazdazeazfazgazhaziazjazkazlazmaznazoazpazqazrazsaztazuazvazzb'aba'baababbacbadbafbagbahbaibajbakbal"
    "bambanbapbaqbarbasbatbavbawbaxbaybazbbabbibbubchbdabdebdibdobdubebbedbegbehbejbekbelbembenbeqberbesbetbeybezbgabgebghbgi"
    "bgobgubhabhibi'biabibbidbigbihbijbikbilbimbinbiqbirbisbitbiubivbiwbiybizbjabjebjubkabkebkhbkibkobkublablebliblubmabnabne"
    "bnibodbogbohbojbokbolbombonboqborbosbotboubovbowboybozbqabrabrebribrubsabshbsibtabtebtibu'buabubbudbugbuhbuibujbukbulbum"
    "bunbuqburbusbutbuvbuybuzbwabyabzabzebzibzucancelch'chachechgchichkchlchmchnchochrchschtchuchvcilconcoocrecroculd'ad'ida'"
    "daadabdaddafdagdahdaidajdakdaldamdandapdaqdardasdatdaudavdawdaydazdbadbedbidbodbudchddaddeddiddoddudebdeddeedegdehdejdek"
    "deldemdendepdeqderdesdetdevdewdeydezdfadgadgedghdgidgodgudhadhidhudiadibdiddifdigdihdijdikdildimdindipdiqdirdisditdivdiw"
    "diydizdjadkadkedkhdkidkodkudladlidludmadmidmodmudnadnidobdoddogdohdokdoldomdondoqdordosdotdoudovdowdozdpadqadqodqudradre"
    "dridrodrudsadsedshdsidsodsudtadtudu'duadubduddufdugduhdujdukduldumdundupduqdurdusdutduvduwduyduzdvadvidwadyadzadzhdzie'a"
    "e'ie'ue-de-ke-qe-re-seatebaebdebeebieblebneboebrebtebuecaecheciectedaeddedeedgediedledmedreduefaefeefiefkeflefreftegaege"
    "eghegieglegoegregsegueh'eh-ehaehbehdeheehgehiehjehkehlehmehnehpehrehsehtehuehyehzejaejeejgejiejlejnejoejtejuekaekeekheki"
    "ekkeklekmekoekreksektekuel'elaelbeldeleelfelgelhelieljelkellelmelneloelpelqelselteluelvelyemaembemdemeemgemiemmemoempems"
    "emuenaenbencendeneengenhenienjenkennenoenqenrensentenuenyenzepaepeepiepkepsepueqaeqdeqeeqieqleqnequeraerbercerdereerferg"
    "erherierjerkerlermerneroerperqerrerserteruerverxeryerzesaesbeseesfesgeshesieskeslesmesnesoespesqesrestesuetaeteetietneto"
    "etretsettetuevaeveevievlevrewaeweewiewrewsewteyaeybeydeyeeyfeygeyheyieyjeykeyleymeyneypeyqeyreyseyteyueyveyyeyzezaezbeze"
    "ezfezgezheziezkezlezmeznezqezrezuezvezzfa'fabfadfaffahfaifajfakfalfamfanfaqfarfasfatfavfawfayfazfchfdafe'fedfehfekfelfen"
    "feqferfesfetfeyfezffafhafiafidfigfijfikfilfinfiqfirfisfitfiyfizfjafkafkhfkuflafliflufmafnafolforfowfqafrafrefrifrufsafsh"
    "ftafteftiftkftufudfulfunfurfusfutfuzfyafzaga'gabgadgafgaggahgajgakgalgamgangapgargasgatgaugavgawgaygazgbagchgdagdegedgeh"
    "gejgelgemgengergesgetgevgewgeygezggaghaghbghdgheghgghighjghkghlghmghnghoghrghsghtghughzgiagibgidgiggijgikgilgimgingiogir"
    "gisgitgivgiygizgjaglagliglugmagnagobgodgoggohgojgolgomgongorgosgotgovgowgozgragregrigrogrugsagtagtegu'guagubgudgufgugguh"
    "gujgukgulgumgungurgusgutguvguyguzgvagwagyagzah'ah'ih-eha'haahabhachadhafhaghahhaihajhakhalhamhanhaphaqharhashathauhavhaw"
    "hayhazhbahbehbihbohbuhchhdahdehdihdohduhe'heahebhechedheehefheghehheihejhekhelhemhenhepheqherheshethevhewhexheyhezhfahfe"
    "hfihfuhgahgehghhgihgohguhhahhehiahibhichidhifhighihhijhikhilhimhinhiqhirhishithiuhivhiwhiyhizhjahjehjihjuhkahkehkhhkihkn"
    "hkohkuhlahlehlihlohluhmahmehmihmuhnahndhnehnihnohnuho'hobhodhofhoghohhojhokholhomhonhoohophoqhorhoshothouhovhowhozhpahpe"
    "hpihpuhqahqehqihqohquhrahrdhrehrihrjhrkhrmhrnhrohruhryhsahsehshhsihsuht-htahtehtihtjhtkhtlhtohtrhtshtuhu'huahubhudhufhug"
    "huhhujhukhulhumhunhuphuqhurhushuthuvhuwhuyhuzhvahvehvihvohwahwihwuhyahyuhzahzehzihzui'ai'ii-ki-yia'iabiadiafiagiahiajiak"
    "ialiamianiapiaqiariasiatiaviayiazibaibdibeibiibkibliboibribuibvicaichiciid-idaidbiddideidgidhidiidjidkidlidmidnidoidrids"
    "iduifaifeiffifiifliftigaigdigeighigiigligoigriguihaiheihiihlihoihrihuijaijeijiijkijlijrijuikaikeikhikiikkiklikmiknikoikr"
    "iksikuil'ilailbildileilgilhiliilkillilniloilrilsiltiluilvilzimaimbimdimeimgimiimjimkimlimmimnimoimrimsimuimzinainbincind"
    "ineinginhiniinjinkinlinninoinqinsintinuinziowipaipiipuiqaiqeiqiiqliquir-irairbirdireirfirgirhiriirjirkirlirmirniroirpirq"
    "irrirsirtiruirvirwiryirzisaiseisgishisiiskislismisnisoispistisuitaiteithitiitkitlitmitrittituiunivaivdiveivgiviivkivoivr"
    "ivsiwaiweiwiiyaiyeiyiiyoiysiyuiyyizaizbizdizeizgizhiziizkizlizmiznizoizrizuizzj'aja'jaajabjadjafjagjahjaijajjakjaljamjan"
    "japjaqjarjasjatjavjawjayjazjbajbojdajdijebjedjegjehjekjeljemjenjeqjerjesjetjeyjezjgajgujhajiajibjidjifjigjihjijjikjiljim"
    "jinjiqjirjisjitjiyjizjjajjejjijkajkujlajlijlujmajmijmujnajnujobjodjogjohjokjoljomjonjoqjorjovjowjozjrajrejrijrujtaju'jua"
    "jubjudjufjugjuhjujjukjuljumjunjuqjurjusjutjuwjuyjuzjvajwajzak'aka'kaakabkadkafkagkahkaikajkakkalkamkankapkaqkarkaskatkau"
    "kavkawkaykazkbakbukchkdakebkedkegkehkekkelkemkenkepkerkesketkewkeykezkfakh-khakhbkhdkhekhfkhgkhikhjkhkkhlkhmkhnkhokhrkhs"
    "khtkhukhvkhwkhzkiakibkidkifkigkijkikkilkimkinkirkiskitkiukivkiykizkjakkakkokkuklaklekliklukmakmeknakniknukobkodkofkohkoj"
    "kokkolkomkonkopkorkoskotkovkowkoykozkrakrekrikrokruksakshksiksuktaktektuku'kuakubkudkufkugkuhkujkukkulkumkunkupkuqkurkus"
    "kutkuvkuwkuykuzkvakwakyakzakzil'al'el'il-al-dl-el-hl-kl-ml-rl-sl-tla'la-laalablacladlaflaglahlailajlaklallamlanlaplaqlar"
    "laslatlavlawlaylazlbalbelbilbolbulchldaldeldildoldule'leblecledlefleglehlejleklellemlenleqlerlesletlevleylezlfalfelfilga"
    "lgelghlgilgolgulhalhelhilholhuli-lialibliclidlifliglihlijliklillimlinlipliqlirlislitlivliwliylizljaljeljiljulkalkelkhlki"
    "lkolkullallellillollulmalmelmilmolmulnalneloclogloklollomlonloqlorloslotlovlowlpalpelpulqalqelqilqolqulralrilrolsalselsh"
    "lsilsultalteltoltulu'lualubludluflugluhlujluklullumlunlupluqlurluslutluvluyluzlvalvelvilwalyalyulzalzim'am'ema'maamabmad"
    "mafmagmahmaimajmakmalmammanmapmaqmarmasmatmaumavmawmaymazmbambembimbkmblmbombrmbumchmdamdemdimdomdume'mecmedmegmehmejmek"
    "melmemmenmeqmermesmetmeymezmfamgamghmgomhamhemhumi'miamibmidmifmigmihmijmikmilmimminmiqmirmismitmivmiwmiymizmjamjemjimka"
    "mkemkhmkimkomkumlamlemlimlummammemmimmumnamnemnimnumo'mobmodmofmogmohmojmokmolmommonmoomoqmormosmotmoumovmowmozmpampimpo"
    "mprmpumqamramremrimromrumsamsemshmsimsumtamtemtimtumu'muamubmudmufmugmuhmujmukmulmummunmuqmurmusmutmuwmuymuzmvamwamyamza"
    "mzemzimzun'an-ena'naanabnadnafnagnahnainajnaknalnamnannaonapnaqnarnasnatnaunavnawnaynaznbanbenbinbonbuncenchncind-ndandb"
    "nddndendgndhndindjndkndlndnndondpndrndundvne'neanebnednefnegnehnejneknelnemnepneqnernesnetnevnewneyneznfanfinfungangbngd"
    "ngenghngingjngknglngongrngsngtngunhanhenhinhuni'ni-nianibnicnidnifnignihnijniknilnimninniqnirnisnitniunivniyniznjanjenji"
    "njknjonjunkankenkhnkinkonkunlanlenlinlunmanminnannennunobnodnofnognohnoknomnoqnornosnotnovnownoznpunqanqenqinqonqunranri"
    "nrunsansenshnsinsonsuntantenthntintontunu'nubnudnufnugnujnuknulnumnunnuqnurnusnutnuwnuynuznvanvinwanyanyunzanzenzhnzinzo"
    "nzuo'ao'bo'eobaobeobiobloboobrocaochodaoddodeodiodkodoodroduofaofeofioflofroftofuogaoghoglogroguohaoheohgohiohlohmohnoho"
    "ohrohsohuojaojeojiojlojnojrojuokaokeokhoknokookroksokuol'ol-olaolboldoleolfolgolholioljolkollolmolnoloolpolqolrolsoltolu"
    "olvolyolzom-omaombomeomgomhomiomjomkomlommomoompomromsomuon'onaonbondoneongonionjonkonoonqonronsontonuonvonyootopaopeopi"
    "opooppopuoqaoqeoqioqloqmoqnoqooqqoqroquoraorbordoreorforgorhoriorjorkormornoroorporqorrorsortoruorvoryorzosaosboseosfosg"
    "oshosioskoslosmosnosqosrossostosuotaotboteotfotiotkotlotootrottotuounovaoveoviovoovrovuovvow'owaowbowdoweowfowgowhowjowk"
    "owlowmownowpowqowrowsowtowvowyowzoyeoyuozaozbozdozeozgozhoziozkozlozmoznozoozpozqozrozuozvpa'pabpadpagpahpaipajpakpalpam"
    "panpappaqparpaspatpavpawpaypazpdupebpecpedpegpehpelpenperpespetpeypezphapiapidpigpikpilpinpirpispitpizpkaplaplupodpolpon"
    "porpospotpowpozppapraprepripropsapshpubpudpugpukpulpumpunpurpusputpuypuzpzaq'aqa'qaaqabqadqafqagqahqajqakqalqamqanqapqaq"
    "qarqasqatqavqawqayqazqbaqbeqbuqchqdaqdeqdiqduqebqeeqehqejqelqemqenqerqesqetqeyqezqiaqibqidqilqimqinqirqisqitqiyqizqjaqla"
    "qliqluqmaqmiqnaqneqobqodqohqojqolqomqonqopqoqqorqosqotqovqowqozqqaqqeqqiqraqriqruqsaqshqtaqtiqubqudqujqukqulqumqunqupqur"
    "qusqutquvquwquyquzqyaqzar'ar'ira'raarabradrafragrahrairajrakralramranraorapraqrarrasratravrawrayrazrbarberbirborburchrd-"
    "rdardbrderdgrdhrdirdjrdkrdlrdmrdnrdordqrdrrdsrdtrdure'rebredreerefregrehrejrekrelremrenrepreqresretrevrewreyrezrfarferfi"
    "rfkrfurgargerghrgirgorgurharherhirhorhuriaribricridrifrigrihrijrikrilrimrinripriqrirrisritrivriyrizrjarjerjirjorjurkarke"
    "rkhrkirklrkorkurlarlerlirlorlurmarmermirmkrmlrmormsrmurnarnernirnornuroarobrodrofrogrohrokrolromronrooroproqrosrourovrow"
    "rozrparperpirporpurqarqerqirqorqurrarrerrirrmrrorrursarsershrsirskrsorsurtarterthrtirtkrtlrtorturu'rubrudrufrugruhruiruj"
    "rukrulrumrunrupruqrurrusrutruvruwruyruzrvarvervirwarwerwirwuryaryeryurzarzbrzdrzerzgrzhrzirzkrzorzrrzus'as'usa'saasabsad"
    "safsagsahsaisajsaksalsamsansapsaqsarsassatsausavsawsaysazsbasbesbisbuschsdasduse'sebsecsedsefsegsehsejsekselsemsensepseq"
    "sersessetsevseysfasfesfisfosfusgasgesghsgisgush'shashbshdsheshfshgshhshishjshkshlshmshnshoshpshqshrshsshtshushvshwshysia"
    "sibsidsifsigsihsijsiksilsimsinsipsiqsirsissitsiusivsiysizsjasjisk-skaskeskhskiskoskuslasleslislusmasmesmismusnasnesniso'"
    "sobsodsofsogsohsoksolsomsonsoosopsoqsorsossotsovsowspaspespispospusqasqusrasresrisrosrussassessistastestgstistkstostrstu"
    "su'subsudsufsugsuhsuisujsuksulsumsunsupsuqsursussutsuvsuwsuysuzsvasviswasweswrsyasyut'ata'taatabtadtaftagtahtaitajtaktal"
    "tamtantaptaqtartastattavtawtaytaztbatbitchtdate-tebtedteftegtehtejtekteltemtentepteqtertestettevtewteyteztfatfitgatgetgi"
    "tguthathethithothrthuti'tiatibtidtiftigtihtijtiktiltimtintiptiqtirtistittiutivtiytiztkatketkhtkotkutlatletlitlutmatmetmi"
    "tnatnitogtohtoktoltomtontootoptoqtortostovtowtqatratretritrotrutsatshttattettittutu'tuatubtudtuftugtuhtujtuktultumtuntup"
    "tuqturtustuttuvtuwtuytuztvatwatyatyuu'au'du'eu'iu'lu'uu'yualuamuanuaruayubaubeubiubkublubnuboubrubuuchudaudbudeudgudhudi"
    "udjudkudludmudnudoudrudsuduufaufeufiufkufluftufuugaugeughugiuglugougrugsuguuh-uhauhduheuhiuhluhmuhouhruhsuhuuiyujaujeuji"
    "ujuukaukeukhukiukjuklukoukruksukuulaulbulduleulfulgulhuliuljulkullulmulnuloulqulsultuluulvulwulyum'umaumbumdumeumiumkuml"
    "ummumnumoumrumsumtumuunaunbunduneunfunguniunjunkunlunnunounqunsuntunuunzupaupeupiupouppuprupuuqauqiuqluqouquur-uraurburd"
    "ureurfurgurhuriurjurkurlurmurnurourpurqurrursurturuurvuryurzusauseusfushusiuskuslusmusnusousrussustusuutautbuteutguthuti"
    "utkutlutmutoutrutsuttutuuvauveuviuvouwauwiuwruyauyeuyjuyluynuyouyruysuytuyuuyzuzauzbuzduzeuzguzhuziuzkuzluznuzouzquzruzs"
    "uzuva'va-vabvadvafvagvahvaivajvakvalvamvanvapvaqvarvasvatvavvayvazvbavchvdavdevduvedvehvekvelvenvervesvetveyvezvgaviavid"
    "vihvijvikvilvimvinvirvisvitviyvizvjavjevkavkevlavlivmavnavodvojvolvonvorvosvowvozvravrevsavshvsivtavudvurvusvvavvovzavzi"
    "w'aw'iw'uwa'wabwacwadwafwahwaiwajwakwalwamwanwaqwarwaswatwawwaywazwbawbewbiwblwbowbuwchwdawdbwdewdiwdlwdswduwelwenwerwes"
    "wezwfawfewfiwgawgewghwgiwgowguwhawhewhiwhuwidwihwijwikwilwinwirwiswitwiywjawjewjiwjuwkawkewkhwkiwkuwlawlewliwlkwlmwlowlu"
    "wmawmbwmewmiwmuwnawndwnewniwnjwnkwpawplwpuwqawquwrawrbwrdwrewrgwriwrjwrkwrmwrnwrowrqwrswrtwruwrzwsawsewshwsiwstwsuwtawte"
    "wtiwtowtuwudwulwurwuswutwvawviwwawwiwyawyewyuwzawzewzhwziwzkwzlwzowzuxalxanxelxerxesxirxurxway'aya'yabyadyafyagyahyajyak"
    "yalyamyanyapyaqyaryasyatyavyawyayyazybaybeybiyboychydaydeydiydlyduye-yebyedyegyehyekyelyemyenyeqyeryesyetyezyfayfeyfiyga"
    "ygeyghygiygoyguyhayhiyhuyidyinyjayjeyjiyjuykaykeykhykiykrykuylayleyliyloyluymaymeymiymoymuyn-ynayneyniynkynoynuyolyoqyor"
    "youyowypaypuyqayqiyquyrayreyrgyriyrkyroyruyrzysayseyshysiystysuytayteythytiytuyubyudyugyuhyujyukyulyumyunyuqyuryusyutyuz"
    "yvayveywaywiyyayydyyeyyiyyuyzayzeyzhyziz'az'iza'zabzadzafzagzahzaizajzakzalzamzanzapzaqzarzaszatzavzawzaxzayzazzbazbezbi"
    "zbozbuzchzdazdezdgzdizduzebzedzeezefzegzehzekzelzemzenzeqzerzeszevzewzeyzfazgazgezghzgizgozguzhazhdzhezhgzhizhmzhnzhuzia"
    "zibzidzifzigzijzikzilzimzinzirziszitzivziwziyzizzjazkazkhzkizkozkuzlazlezlizlozluzmazmezmizmuznaznezniznuzobzogzohzolzom"
    "zonzorzovzowzozzpazpizqazqezqozquzr'zrazrezrizruzsazshztaztizu'zubzufzugzuhzujzukzulzumzunzuqzurzuszuwzuyzuzzvazvizwazya"
    "zyuzzazzi";

#include "inline/common-roots.inl"

} // namespace arabic
} // namespace mk
