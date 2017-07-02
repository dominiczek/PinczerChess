#include "allMoves.h"

short bishopMovesCount[64] = {7,7,7,7,7,7,7,7, 7,9,9,9,9,9,9,7, 7,9,11,11,11,11,9,7, 7,9,11,13,13,11,9,7, 7,9,11,13,13,11,9,7, 7,9,11,11,11,11,9,7, 7,9,9,9,9,9,9,7, 7,7,7,7,7,7,7,7};
short queenMovesCount[64] = {21,21,21,21,21,21,21,21, 21,23,23,23,23,23,23,21, 21,23,25,25,25,25,23,21, 21,23,25,27,27,25,23,21, 21,23,25,27,27,25,23,21, 21,23,25,25,25,25,23,21, 21,23,23,23,23,23,23,21, 21,21,21,21,21,21,21,21};
short kingMovesCount[64] = {3,5,5,5,5,5,5,3, 5,8,8,8,8,8,8,5, 5,8,8,8,8,8,8,5, 5,8,8,8,8,8,8,5, 5,8,8,8,8,8,8,5, 5,8,8,8,8,8,8,5, 5,8,8,8,8,8,8,5, 3,5,5,5,5,5,5,3};
short rookMovesCount[64] = {14};
short knightMovesCount[64] = {2,3,4,4,4,4,3,2, 3,4,6,6,6,6,4,3, 4,6,8,8,8,8,6,4, 4,6,8,8,8,8,6,4, 4,6,8,8,8,8,6,4, 4,6,8,8,8,8,6,4, 3,4,6,6,6,6,4,3, 2,3,4,4,4,4,3,2};

DIRECTION bishopDirections[] = {NE, SE, SW, NW};
DIRECTION rookDirections[] = {N, E, S, W};
DIRECTION queenkDirections[] = {N, NE, E, SE, S, SW, W, NW};
DIRECTION kingDirections[] = {N, NE, E, SE, S, SW, W, NW};

const U64 pawnCaptures[2][64] = 
{
	{ 
		0,0, 0, 0, 0, 0, 0, 0,
		131072, 327680, 655360, 1310720, 2621440, 5242880, 10485760, 4194304, 
		33554432, 83886080, 167772160, 335544320, 671088640, 1342177280, 2684354560, 1073741824, 
		8589934592, 21474836480, 42949672960, 85899345920, 171798691840, 343597383680, 687194767360, 274877906944, 
		2199023255552, 5497558138880, 10995116277760, 21990232555520, 43980465111040, 87960930222080, 175921860444160, 70368744177664, 
		562949953421312, 1407374883553280, 2814749767106560, 5629499534213120, 11258999068426240, 22517998136852480, 45035996273704960, 18014398509481984, 
		144115188075855872, 360287970189639680, 720575940379279360, 1441151880758558720, 2882303761517117440, 5764607523034234880, 11529215046068469760, 4611686018427387904, 
		0,0, 0, 0, 0, 0, 0, 0
	},
	{ 
		0, 0, 0, 0, 0, 0, 0, 0, 
		2, 5, 10, 20, 40, 80, 160, 64, 
		512, 1280, 2560, 5120, 10240, 20480, 40960, 16384, 
		131072, 327680, 655360, 1310720, 2621440, 5242880, 10485760, 4194304, 
		33554432, 83886080, 167772160, 335544320, 671088640, 1342177280, 2684354560, 1073741824, 
		8589934592, 21474836480, 42949672960, 85899345920, 171798691840, 343597383680, 687194767360, 274877906944, 
		2199023255552, 5497558138880, 10995116277760, 21990232555520, 43980465111040, 87960930222080, 175921860444160, 70368744177664, 
		0,0, 0, 0, 0, 0, 0, 0
	}
};


const U64 bishopMoves[64][4] = {
	{ 9241421688590303744, 0, 0, 0},
	{ 36099303471055872, 0, 0, 256},
	{ 141012904183808, 0, 0, 66048},
	{ 550831656960, 0, 0, 16909312},
	{ 2151686144, 0, 0, 4328785920},
	{ 8404992, 0, 0, 1108169199616},
	{ 32768, 0, 0, 283691315109888},
	{ 0, 0, 0, 72624976668147712},

	{ 4620710844295151616, 2, 0, 0},
	{ 9241421688590303232, 4, 1, 65536},
	{ 36099303471054848, 8, 2, 16908288},
	{ 141012904181760, 16, 4, 4328783872},
	{ 550831652864, 32, 8, 1108169195520},
	{ 2151677952, 64, 16, 283691315101696},
	{ 8388608, 128, 32, 72624976668131328},
	{ 0, 0, 64, 145249953336262656},
	{ 2310355422147510272, 516, 0, 0},
	{ 4620710844295020544, 1032, 256, 16777216},
	{ 9241421688590041088, 2064, 513, 4328521728},
	{ 36099303470530560, 4128, 1026, 1108168671232},
	{ 141012903133184, 8256, 2052, 283691314053120},
	{ 550829555712, 16512, 4104, 72624976666034176},
	{ 2147483648, 32768, 8208, 145249953332068352},
	{ 0, 0, 16416, 290499906664136704},

	{ 1155177711056977920, 132104, 0, 0},
	{ 2310355422113955840, 264208, 65536, 4294967296},
	{ 4620710844227911680, 528416, 131328, 1108101562368},
	{ 9241421688455823360, 1056832, 262657, 283691179835392},
	{ 36099303202095104, 2113664, 525314, 72624976397598720},
	{ 141012366262272, 4227072, 1050628, 145249952795197440},
	{ 549755813888, 8388608, 2101256, 290499905590394880},
	{ 0, 0, 4202512, 580999811180789760},
	{ 577588851233521664, 33818640, 0, 0},
	{ 1155177702467043328, 67637280, 16777216, 1099511627776},
	{ 2310355404934086656, 135274560, 33619968, 283673999966208},
	{ 4620710809868173312, 270549120, 67240192, 72624942037860352},
	{ 9241421619736346624, 541097984, 134480385, 145249884075720704},

	{ 36099165763141632, 1082130432, 268960770, 290499768151441408},
	{ 140737488355328, 2147483648, 537921540, 580999536302882816},
	{ 0, 0, 1075843080, 1161999072605765632},
	{ 288793326105133056, 8657571872, 0, 0},
	{ 577586652210266112, 17315143744, 4294967296, 281474976710656},
	{ 1155173304420532224, 34630287488, 8606711808, 72620543991349248},
	{ 2310346608841064448, 69260574720, 17213489152, 145241087982698496},

	{ 4620693217682128896, 138521083904, 34426978560, 290482175965396992},
	{ 9241386435364257792, 277025390592, 68853957121, 580964351930793984},
	{ 36028797018963968, 549755813888, 137707914242, 1161928703861587968},
	{ 0, 0, 275415828484, 2323857407723175936},
	{ 144115188075855872, 2216338399296, 0, 0},
	{ 288230376151711744, 4432676798592, 1099511627776, 72057594037927936},
	{ 576460752303423488, 8865353596928, 2203318222848, 144115188075855872},
	{ 1152921504606846976, 17730707128320, 4406653222912, 288230376151711744},
	{ 2305843009213693952, 35461397479424, 8813306511360, 576460752303423488},
	{ 4611686018427387904, 70918499991552, 17626613022976, 1152921504606846976},
	{ 9223372036854775808, 140737488355328, 35253226045953, 2305843009213693952},
	{ 0, 0, 70506452091906, 4611686018427387904},

	{ 0, 567382630219904, 0, 0},
	{ 0, 1134765260439552, 281474976710656, 0},
	{ 0, 2269530520813568, 564049465049088, 0},
	{ 0, 4539061024849920, 1128103225065472, 0},
	{ 0, 9078117754732544, 2256206466908160, 0},
	{ 0, 18155135997837312, 4512412933881856, 0 },
	{ 0, 36028797018963968, 9024825867763968, 0 },
	{ 0, 0, 18049651735527937, 0 }
};


const U64 kingMoves[64] = {
	770,
	1797,
	3594,
	7188,
	14376,
	28752,
	57504,
	49216,
	197123,
	460039,
	920078,
	1840156,
	3680312,
	7360624,
	14721248,
	12599488,
	50463488,
	117769984,
	235539968,
	471079936,
	942159872,
	1884319744,
	3768639488,
	3225468928,
	12918652928,
	30149115904,
	60298231808,
	120596463616,
	241192927232,
	482385854464,
	964771708928,
	825720045568,
	3307175149568,
	7718173671424,
	15436347342848,
	30872694685696,
	61745389371392,
	123490778742784,
	246981557485568,
	211384331665408,
	846636838289408,
	1975852459884544,
	3951704919769088,
	7903409839538176,
	15806819679076352,
	31613639358152704,
	63227278716305408,
	54114388906344448,
	216739030602088448,
	505818229730443264,
	1011636459460886528,
	2023272918921773056,
	4046545837843546112,
	8093091675687092224,
	16186183351374184448,
	13853283560024178688,
	144959613005987840,
	362258295026614272,
	724516590053228544,
	1449033180106457088,
	2898066360212914176,
	5796132720425828352,
	11592265440851656704,
	4665729213955833856
};
	
	
const U64 knightMoves[64] ={
	132096,
	329728,
	659712,
	1319424,
	2638848,
	5277696,
	10489856,
	4202496,
	33816580,
	84410376,
	168886289,
	337772578,
	675545156,
	1351090312,
	2685403152,
	1075839008,
	8657044482,
	21609056261,
	43234889994,
	86469779988,
	172939559976,
	345879119952,
	687463207072,
	275414786112,
	2216203387392,
	5531918402816,
	11068131838464,
	22136263676928,
	44272527353856,
	88545054707712,
	175990581010432,
	70506185244672,
	567348067172352,
	1416171111120896,
	2833441750646784,
	5666883501293568,
	11333767002587136,
	22667534005174272,
	45053588738670592,
	18049583422636032,
	145241105196122112,
	362539804446949376,
	725361088165576704,
	1450722176331153408,
	2901444352662306816,
	5802888705324613632,
	11533718717099671552,
	4620693356194824192,
	288234782788157440,
	576469569871282176,
	1224997833292120064,
	2449995666584240128,
	4899991333168480256,
	9799982666336960512,
	1152939783987658752,
	2305878468463689728,
	1128098930098176,
	2257297371824128,
	4796069720358912,
	9592139440717824,
	19184278881435648,
	38368557762871296,
	4679521487814656,
	9077567998918656
};

const U64 rookMoves[64][4] = {
	{ 72340172838076672,   254,   0,   0},
	{ 144680345676153344,   252,   0,   1},
	{ 289360691352306688,   248,   0,   3},
	{ 578721382704613376,   240,   0,   7},
	{ 1157442765409226752,   224,   0,   15},
	{ 2314885530818453504,   192,   0,   31},
	{ 4629771061636907008,   128,   0,   63},
	{ 9259542123273814016,   0,   0,   127},
	{ 72340172838076416,   65024,   1,   0},
	{ 144680345676152832,   64512,   2,   256},
	{ 289360691352305664,   63488,   4,   768},
	{ 578721382704611328,   61440,   8,   1792},
	{ 1157442765409222656,   57344,   16,   3840},
	{ 2314885530818445312,   49152,   32,   7936},
	{ 4629771061636890624,   32768,   64,   16128},
	{ 9259542123273781248,   0,   128,   32512},
	{ 72340172838010880,   16646144,   257,   0},
	{ 144680345676021760,   16515072,   514,   65536},
	{ 289360691352043520,   16252928,   1028,   196608},
	{ 578721382704087040,   15728640,   2056,   458752},
	{ 1157442765408174080,   14680064,   4112,   983040},
	{ 2314885530816348160,   12582912,   8224,   2031616},
	{ 4629771061632696320,   8388608,   16448,   4128768},
	{ 9259542123265392640,   0,   32896,   8323072},
	{ 72340172821233664,   4261412864,   65793,   0},
	{ 144680345642467328,   4227858432,   131586,   16777216},
	{ 289360691284934656,   4160749568,   263172,   50331648},
	{ 578721382569869312,   4026531840,   526344,   117440512},
	{ 1157442765139738624,   3758096384,   1052688,   251658240},
	{ 2314885530279477248,   3221225472,   2105376,   520093696},
	{ 4629771060558954496,   2147483648,   4210752,   1056964608},
	{ 9259542121117908992,   0,   8421504,   2130706432},
	{ 72340168526266368,   1090921693184,   16843009,   0},
	{ 144680337052532736,   1082331758592,   33686018,   4294967296},
	{ 289360674105065472,   1065151889408,   67372036,   12884901888},
	{ 578721348210130944,   1030792151040,   134744072,   30064771072},
	{ 1157442696420261888,   962072674304,   269488144,   64424509440},
	{ 2314885392840523776,   824633720832,   538976288,   133143986176},
	{ 4629770785681047552,   549755813888,   1077952576,   270582939648},
	{ 9259541571362095104,   0,   2155905152,   545460846592},
	{ 72339069014638592,   279275953455104,   4311810305,   0},
	{ 144678138029277184,   277076930199552,   8623620610,   1099511627776},
	{ 289356276058554368,   272678883688448,   17247241220,   3298534883328},
	{ 578712552117108736,   263882790666240,   34494482440,   7696581394432},
	{ 1157425104234217472,   246290604621824,   68988964880,   16492674416640},
	{ 2314850208468434944,   211106232532992,   137977929760,   34084860461056},
	{ 4629700416936869888,   140737488355328,   275955859520,   69269232549888},
	{ 9259400833873739776,   0,   551911719040,   139637976727552},
	{ 72057594037927936,   71494644084506624,   1103823438081,   0},
	{ 144115188075855872,   70931694131085312,   2207646876162,   281474976710656},
	{ 288230376151711744,   69805794224242688,   4415293752324,   844424930131968},
	{ 576460752303423488,   67553994410557440,   8830587504648,   1970324836974592},
	{ 1152921504606846976,   63050394783186944,   17661175009296,   4222124650659840},
	{ 2305843009213693952,   54043195528445952,   35322350018592,   8725724278030336},
	{ 4611686018427387904,   36028797018963968,   70644700037184,   17732923532771328},
	{ 9223372036854775808,   0,   141289400074368,   35747322042253312},
	{ 0,   18302628885633695744,   282578800148737,   0},
	{ 0,   18158513697557839872,   565157600297474,   72057594037927936},
	{ 0,   17870283321406128128,   1130315200594948,   216172782113783808},
	{ 0,   17293822569102704640,   2260630401189896,   504403158265495552},
	{ 0,   16140901064495857664,   4521260802379792,   1080863910568919040},
	{ 0,   13835058055282163712,   9042521604759584,   2233785415175766016},
	{ 0,   9223372036854775808,   18085043209519168,   4539628424389459968},
	{ 0,   0,   36170086419038336,   9151314442816847872}
};


		
const U64 queenMoves[64][8] = {
	{ 72340172838076672, 9241421688590303744, 254, 0, 0, 0, 0, 0},
	{ 144680345676153344, 36099303471055872, 252, 0, 0, 0, 1, 256},
	{ 289360691352306688, 141012904183808, 248, 0, 0, 0, 3, 66048},
	{ 578721382704613376, 550831656960, 240, 0, 0, 0, 7, 16909312},
	{ 1157442765409226752, 2151686144, 224, 0, 0, 0, 15, 4328785920},
	{ 2314885530818453504, 8404992, 192, 0, 0, 0, 31, 1108169199616},
	{ 4629771061636907008, 32768, 128, 0, 0, 0, 63, 283691315109888},
	{ 9259542123273814016, 0, 0, 0, 0, 0, 127, 72624976668147712},
	{ 72340172838076416, 4620710844295151616, 65024, 2, 1, 0, 0, 0},
	{ 144680345676152832, 9241421688590303232, 64512, 4, 2, 1, 256, 65536},
	{ 289360691352305664, 36099303471054848, 63488, 8, 4, 2, 768, 16908288},
	{ 578721382704611328, 141012904181760, 61440, 16, 8, 4, 1792, 4328783872},
	{ 1157442765409222656, 550831652864, 57344, 32, 16, 8, 3840, 1108169195520},
	{ 2314885530818445312, 2151677952, 49152, 64, 32, 16, 7936, 283691315101696},
	{ 4629771061636890624, 8388608, 32768, 128, 64, 32, 16128, 72624976668131328},
	{ 9259542123273781248, 0, 0, 0, 128, 64, 32512, 145249953336262656},
	{ 72340172838010880, 2310355422147510272, 16646144, 516, 257, 0, 0, 0},
	{ 144680345676021760, 4620710844295020544, 16515072, 1032, 514, 256, 65536, 16777216},
	{ 289360691352043520, 9241421688590041088, 16252928, 2064, 1028, 513, 196608, 4328521728},
	{ 578721382704087040, 36099303470530560, 15728640, 4128, 2056, 1026, 458752, 1108168671232},
	{ 1157442765408174080, 141012903133184, 14680064, 8256, 4112, 2052, 983040, 283691314053120},
	{ 2314885530816348160, 550829555712, 12582912, 16512, 8224, 4104, 2031616, 72624976666034176},
	{ 4629771061632696320, 2147483648, 8388608, 32768, 16448, 8208, 4128768, 145249953332068352},
	{ 9259542123265392640, 0, 0, 0, 32896, 16416, 8323072, 290499906664136704},
	{ 72340172821233664, 1155177711056977920, 4261412864, 132104, 65793, 0, 0, 0},
	{ 144680345642467328, 2310355422113955840, 4227858432, 264208, 131586, 65536, 16777216, 4294967296},
	{ 289360691284934656, 4620710844227911680, 4160749568, 528416, 263172, 131328, 50331648, 1108101562368},
	{ 578721382569869312, 9241421688455823360, 4026531840, 1056832, 526344, 262657, 117440512,
			283691179835392},
	{ 1157442765139738624, 36099303202095104, 3758096384, 2113664, 1052688, 525314, 251658240,
			72624976397598720},
	{ 2314885530279477248, 141012366262272, 3221225472, 4227072, 2105376, 1050628, 520093696,
			145249952795197440},
	{ 4629771060558954496, 549755813888, 2147483648, 8388608, 4210752, 2101256, 1056964608,
			290499905590394880},
	{ 9259542121117908992, 0, 0, 0, 8421504, 4202512, 2130706432, 580999811180789760},
	{ 72340168526266368, 577588851233521664, 1090921693184, 33818640, 16843009, 0, 0, 0},
	{ 144680337052532736, 1155177702467043328, 1082331758592, 67637280, 33686018, 16777216, 4294967296,
			1099511627776},
	{ 289360674105065472, 2310355404934086656, 1065151889408, 135274560, 67372036, 33619968, 12884901888,
			283673999966208},
	{ 578721348210130944, 4620710809868173312, 1030792151040, 270549120, 134744072, 67240192, 30064771072,
			72624942037860352},
	{ 1157442696420261888, 9241421619736346624, 962072674304, 541097984, 269488144, 134480385, 64424509440,
			145249884075720704},
	{ 2314885392840523776, 36099165763141632, 824633720832, 1082130432, 538976288, 268960770, 133143986176,
			290499768151441408},
	{ 4629770785681047552, 140737488355328, 549755813888, 2147483648, 1077952576, 537921540, 270582939648,
			580999536302882816},
	{ 9259541571362095104, 0, 0, 0, 2155905152, 1075843080, 545460846592, 1161999072605765632},
	{ 72339069014638592, 288793326105133056, 279275953455104, 8657571872, 4311810305, 0, 0, 0},
	{ 144678138029277184, 577586652210266112, 277076930199552, 17315143744, 8623620610, 4294967296,
			1099511627776, 281474976710656},
	{ 289356276058554368, 1155173304420532224, 272678883688448, 34630287488, 17247241220, 8606711808,
			3298534883328, 72620543991349248},
	{ 578712552117108736, 2310346608841064448, 263882790666240, 69260574720, 34494482440, 17213489152,
			7696581394432, 145241087982698496},
	{ 1157425104234217472, 4620693217682128896, 246290604621824, 138521083904, 68988964880, 34426978560,
			16492674416640, 290482175965396992},
	{ 2314850208468434944, 9241386435364257792, 211106232532992, 277025390592, 137977929760, 68853957121,
			34084860461056, 580964351930793984},
	{ 4629700416936869888, 36028797018963968, 140737488355328, 549755813888, 275955859520, 137707914242,
			69269232549888, 1161928703861587968},
	{ 9259400833873739776, 0, 0, 0, 551911719040, 275415828484, 139637976727552, 2323857407723175936},
	{ 72057594037927936, 144115188075855872, 71494644084506624, 2216338399296, 1103823438081, 0, 0, 0},
	{ 144115188075855872, 288230376151711744, 70931694131085312, 4432676798592, 2207646876162, 1099511627776,
			281474976710656, 72057594037927936},
	{ 288230376151711744, 576460752303423488, 69805794224242688, 8865353596928, 4415293752324, 2203318222848,
			844424930131968, 144115188075855872},
	{ 576460752303423488, 1152921504606846976, 67553994410557440, 17730707128320, 8830587504648, 4406653222912,
			1970324836974592, 288230376151711744},
	{ 1152921504606846976, 2305843009213693952, 63050394783186944, 35461397479424, 17661175009296,
			8813306511360, 4222124650659840, 576460752303423488},
	{ 2305843009213693952, 4611686018427387904, 54043195528445952, 70918499991552, 35322350018592,
			17626613022976, 8725724278030336, 1152921504606846976},
	{ 4611686018427387904, 9223372036854775808, 36028797018963968, 140737488355328, 70644700037184,
			35253226045953, 17732923532771328, 2305843009213693952},
	{ 9223372036854775808, 0, 0, 0, 141289400074368, 70506452091906, 35747322042253312, 4611686018427387904},
	{ 0, 0, 18302628885633695744, 567382630219904, 282578800148737, 0, 0, 0},
	{ 0, 0, 18158513697557839872, 1134765260439552, 565157600297474, 281474976710656, 72057594037927936, 0},
	{ 0, 0, 17870283321406128128, 2269530520813568, 1130315200594948, 564049465049088, 216172782113783808, 0},
	{ 0, 0, 17293822569102704640, 4539061024849920, 2260630401189896, 1128103225065472, 504403158265495552, 0},
	{ 0, 0, 16140901064495857664, 9078117754732544, 4521260802379792, 2256206466908160, 1080863910568919040, 0},
	{ 0, 0, 13835058055282163712, 18155135997837312, 9042521604759584, 4512412933881856, 2233785415175766016, 0},
	{ 0, 0, 9223372036854775808, 36028797018963968, 18085043209519168, 9024825867763968, 4539628424389459968, 0},
	{ 0, 0, 0, 0, 36170086419038336, 18049651735527937, 9151314442816847872, 0} 			
};

