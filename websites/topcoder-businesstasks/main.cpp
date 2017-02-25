#include "gtest/gtest.h"

#include <string>
#include <vector>

#include SPECIFIC_HEADER

// Running tests

TEST(TEST_NAME, Example0)
{
  auto data = std::vector<std::string>{"a","b","c","d"};
  ASSERT_EQ("a", business_tasks(data, 2));
}
TEST(TEST_NAME, Example1)
{
  auto data = std::vector<std::string>{"a","b","c","d","e"};
  ASSERT_EQ("d", business_tasks(data, 3));
}
TEST(TEST_NAME, Example2)
{
  auto data = std::vector<std::string>{"alpha","beta","gamma","delta","epsilon"};
  ASSERT_EQ("epsilon", business_tasks(data, 1));
}
TEST(TEST_NAME, Example3)
{
  auto data = std::vector<std::string>{"a","b"};
  ASSERT_EQ("a", business_tasks(data, 1000));
}
TEST(TEST_NAME, Example4)
{
  auto data = std::vector<std::string>{"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t",
"u","v","w","x","y","z"};
  ASSERT_EQ("n", business_tasks(data, 17));
}
TEST(TEST_NAME, Example5)
{
  auto data = std::vector<std::string>{"zlqamum","yjsrpybmq","tjllfea","fxjqzznvg","nvhekxr","am","skmazcey","piklp",
"olcqvhg","dnpo","bhcfc","y","h","fj","bjeoaxglt","oafduixsz","kmtbaxu",
"qgcxjbfx","my","mlhy","bt","bo","q"};
  ASSERT_EQ("fxjqzznvg", business_tasks(data, 9000000));
}

TEST(TEST_NAME, Extended0)
{
  auto data = std::vector<std::string>{"l", "celzw", "vp", "n", "nkmyi", "uaquiikr", "tgu"};
  ASSERT_EQ("nkmyi", business_tasks(data, 7836541));
}
TEST(TEST_NAME, Extended1)
{
  auto data = std::vector<std::string>{"yhvadcqtq", "myr", "mjoyirny", "nofaqvinol", "trxphmasx", "yblchjotr"};
  ASSERT_EQ("trxphmasx", business_tasks(data, 5561784));
}
TEST(TEST_NAME, Extended2)
{
  auto data = std::vector<std::string>{"dfnm", "k"};
  ASSERT_EQ("dfnm", business_tasks(data, 4147202));
}
TEST(TEST_NAME, Extended3)
{
  auto data = std::vector<std::string>{"jegzlqohby", "gvscbzrxvq", "yoznfwvxfr", "wtprk", "zmvqlj", "ughtyb", "cgdincc", "ztsuv", "i", "ba", "jotel", "jwn", "erfhr", "zdhxgfnf", "hkclj", "pfqy", "fkfrxvnp", "dzmucuzru", "oqhaob", "v", "mgbiukmk", "rqykcqogwl", "ot", "f", "mam", "bag", "ildun", "qtlof", "xvlcbdl", "fedopz", "nl"};
  ASSERT_EQ("bag", business_tasks(data, 3827158));
}
TEST(TEST_NAME, Extended4)
{
  auto data = std::vector<std::string>{"tigcvzlb", "u", "cj", "e", "snaa", "hbbskf", "qxkryjwb", "bvbbh", "gzykeeq", "mqfnxhrsj", "zkwvueony", "gsjpvjd", "svbmtbpn", "u", "f", "dqgrpjyuo", "uja", "qopqpekf", "wnbykja", "newod", "xrav", "hvj", "owshyj", "sbsmy", "gy", "a", "utlrl", "zmucefteia", "mnfwmboja", "aki", "wcotsl", "cxjzjib", "dsg", "ksaj", "fl", "thburj", "spwzxryca", "ytbxi", "smevxiu", "uiumrxzu", "dei", "azciontn", "ceymjemr", "geiemwcx", "nsltfgf", "xkmn"};
  ASSERT_EQ("zmucefteia", business_tasks(data, 9046852));
}
TEST(TEST_NAME, Extended5)
{
  auto data = std::vector<std::string>{"wl", "n", "hoykptlh", "q", "ztbjmxzaij", "eoqqre", "nwsimbuda", "fo"};
  ASSERT_EQ("n", business_tasks(data, 3152975));
}
TEST(TEST_NAME, Extended6)
{
  auto data = std::vector<std::string>{"pwerpci", "k", "budsz", "cx", "h", "zheoihfv", "aeipe", "ewsvaqw", "ofvgcol", "kxlqvbfyb", "wqlofv", "gcwhnfhz", "a", "lv", "pltwcxoz", "yi", "nodixfm", "ujdp", "avkvju", "wplzbwdkz", "pajqlyppx", "kpigbest", "bthx", "gblg", "ivb", "zwgybnnctw", "c", "tbinyfef", "lbabny", "i", "qtzhruv", "azcbbhg", "rxkpz", "vvsr", "zvzpbkxu", "ncduwugkp", "cahiajuq", "mwckvuusha", "w"};
  ASSERT_EQ("bthx", business_tasks(data, 10000000));
}
TEST(TEST_NAME, Extended7)
{
  auto data = std::vector<std::string>{"m", "sfm", "bapvgub", "bosipszswv", "vxtiqb", "igmp", "frefavvk", "yqhmuuki", "xsvqfmnqq", "eoapz", "axie", "rrunom", "loqcvirps", "i", "wlwnllmuyf", "uxxbhbiwc", "vpxsh", "wibe", "yucpzyibot", "gulhkimtks", "hhfbjwb", "axmqbmos", "tidlxi", "popojggnjo", "fsr", "vaxh", "ia", "bkvyv", "cjlgxbo", "drohy", "vjchr", "buwbn", "cnzko", "u", "pqw", "e", "to", "dmm", "spfyinx", "caq", "df", "orbttkgsv", "mlihgy", "mqdddbdvzb", "hmlhs"};
  ASSERT_EQ("dmm", business_tasks(data, 3736222));
}
TEST(TEST_NAME, Extended8)
{
  auto data = std::vector<std::string>{"koaejpc", "cysaeugsy", "wtinkacu", "wbzqwqhzy", "darwcliciz", "dnjlb", "i", "y"};
  ASSERT_EQ("wtinkacu", business_tasks(data, 4321174));
}
TEST(TEST_NAME, Extended9)
{
  auto data = std::vector<std::string>{"o", "ylk", "ewaverppb", "hcvynep", "p", "yfecfjbf", "o", "hro", "dxiwuh", "rdos", "crst", "sqtrt", "nv", "ug", "zeqo", "zfuny", "pkarll", "t", "qnc", "pvryln", "obfmfieow", "oidv", "foltqydbe", "td", "ixwulf", "hkwctdrek", "msjb", "mbyl", "wkwvosnq", "ltf", "xqptmp", "lqsuozgu", "n", "rncz", "vgyoe", "dcp", "o", "tp", "th", "dfpmh", "gdgot", "qophtwcok", "paeesnpvff", "zrb", "f", "zvhstd", "ygaatrtzld", "txhvwfito", "ggd"};
  ASSERT_EQ("o", business_tasks(data, 8435322));
}
TEST(TEST_NAME, Extended10)
{
  auto data = std::vector<std::string>{"mdgyiwvw", "pvirakih", "v", "h", "trigbt", "dv", "rhys", "mmlkv", "kkayj", "maojwbdo", "fxavmlhkgg", "pafhmu", "gkmbxph", "cy", "apedrdzph", "flsq", "rio", "ramsbpxpd", "dmee", "zqw", "a", "gvxyhfa", "hg", "rcqjdjdkbc", "j", "oilmsv", "vicx", "vryhznxork", "t", "ix", "txuazrkk", "bmsy", "tadihl", "enqxnrbpwn", "huedzg", "jz", "nlgsbj", "resnkbvxyk", "d", "rcmzu", "pmrbdhteki", "xuamzyvvtq", "ztx", "azycdpb", "m", "bdsqh", "nznmhkzu", "w", "f", "bxh"};
  ASSERT_EQ("vryhznxork", business_tasks(data, 7718687));
}
TEST(TEST_NAME, Extended11)
{
  auto data = std::vector<std::string>{"rwjcnpb", "kfcfv", "znxgcjwwik", "w", "rwvajuce", "xewmhzhjwh", "zjkaap", "s", "iqwarieae", "zerlz", "u", "d", "pzqitbhyq", "ciipw", "asikhdolnb", "foca", "vkjepfo", "s", "krxpwxfllw", "f"};
  ASSERT_EQ("rwjcnpb", business_tasks(data, 2588819));
}
TEST(TEST_NAME, Extended12)
{
  auto data = std::vector<std::string>{"pqhxob", "muwy", "upkyms", "gazkjfgu", "bnokf", "ajzkzefh", "zmzjqtv", "ke", "bhkdnqf"};
  ASSERT_EQ("bhkdnqf", business_tasks(data, 1));
}
TEST(TEST_NAME, Extended13)
{
  auto data = std::vector<std::string>{"uwcojz", "aayecqwi", "ua", "mnknran", "as", "utgpear", "yrghieqg", "dtklrkxru", "qob", "cb", "stxm", "bcwhg"};
  ASSERT_EQ("ua", business_tasks(data, 6123820));
}
TEST(TEST_NAME, Extended14)
{
  auto data = std::vector<std::string>{"qsxtyd", "k", "olt", "fhr", "cljigdbi", "ywwjxvsf", "x", "tfqfxtgiz", "hza", "jzkfllguae", "utvg", "ptkb", "ccecitz", "sxkjnqysbg", "mkxtkbebuw", "sjp", "st", "wk", "fztutk", "mbkfkk", "pvgehs", "zramf", "gzhewp", "l", "rwvzsquegk", "kqtwvmd", "akwum", "jtniaqtr", "jwmxrl", "ruo", "pzcui", "lj", "gipqr", "cbxli", "vwtfpq", "ycovlvezx", "ydrccpw", "bu", "bsygu", "btknkhityr", "jgnoex"};
  ASSERT_EQ("sjp", business_tasks(data, 8349319));
}
TEST(TEST_NAME, Extended15)
{
  auto data = std::vector<std::string>{"vuulw", "dvac", "pjm", "yntzwsnk", "vrcz"};
  ASSERT_EQ("pjm", business_tasks(data, 7118670));
}
TEST(TEST_NAME, Extended16)
{
  auto data = std::vector<std::string>{"bvgr", "y", "v", "hgaqw", "xffdiwcb", "lfkkk", "nsitos", "l", "zfknzt", "lzfwcy", "kgubzn", "jsamkngab", "snyynssuzi", "rh", "yebb", "uvbc", "ghgqsarhul", "fchtdybnk", "yqxfhcpsmm", "u", "mpqcndgcc", "docpudvfm", "im", "labyetelv", "fditwda", "hlguuvi", "wwwxgr", "a", "wtog", "ftvqp", "pz", "npvv", "viseblclg", "k", "y"};
  ASSERT_EQ("ftvqp", business_tasks(data, 4891354));
}
TEST(TEST_NAME, Extended17)
{
  auto data = std::vector<std::string>{"qggyfqmnz", "yxspcfoung", "ktdm", "ij", "nodbvhgrjq", "wtxieknfx", "mwqzremz", "rjhqeaym", "jdwbwk", "guu", "hatpz", "fgaxgrecuk", "dbhucxo", "xormvizr", "vicyyadn", "behnros", "aygpilxcs", "jmrw", "nm", "ly", "wbvyji", "ktbe", "qwbedx", "r", "qkyaodwia", "evloffb", "jimidghfkp", "wzcauotc", "umbwrlrr", "hedjz", "k", "j", "hfiufqus", "d", "iex", "hmfr", "yehvvkrfd", "acsfehaf", "gzfn"};
  ASSERT_EQ("k", business_tasks(data, 8380305));
}
TEST(TEST_NAME, Extended18)
{
  auto data = std::vector<std::string>{"faf", "jazdoodk", "ywmwl", "gxhyrmwc", "rhuxbf", "migzdyhp", "qussxdptit", "wiiuh", "l", "coln", "atfwrt", "igvazctdx", "vku", "woab", "h", "ndbdig", "aofgaqyfo", "uekhmz", "pijljzbe", "itrvzl", "regbhiobq", "li", "jd", "sy", "rpy", "wdfskw", "xtw", "kzbhqow", "tg", "w", "uj"};
  ASSERT_EQ("gxhyrmwc", business_tasks(data, 845));
}
TEST(TEST_NAME, Extended19)
{
  auto data = std::vector<std::string>{"blhrqkjb", "amdx", "czrg", "rjtlrkk", "ot", "qe", "qhztfnb", "dqtq", "jacbegc", "v", "xfrbmc", "cferlfdon", "jzxoy", "oqodwdohkp", "fvuuzhbmc", "wqax", "ubikflhdfc", "fvfdirmmts", "r", "yognjjwm", "qzihgkc", "rzl", "ouqwshcut", "es", "yrjvbqj", "daiaprcfy", "jgukgz"};
  ASSERT_EQ("ubikflhdfc", business_tasks(data, 41));
}
TEST(TEST_NAME, Extended20)
{
  auto data = std::vector<std::string>{"ufopvla", "volnicf", "vzhnvebph", "nx", "ar", "orh", "zfm", "mijolmlqq", "wqretzv", "snajzf", "o", "igcipg", "b", "gmzn", "xjcixrv", "pxmg", "slhfh", "iyoryw", "j", "tf", "jmeani", "e", "lrsfyfu", "arho", "rkdbbod", "y", "j", "guc", "ob", "ywfto", "xmq", "trwou", "gbchxg", "uyarlnculn", "lbrovr", "spqeqhq", "daj", "ns", "eaypuhvepk", "cndcgx", "hqgihacbep", "njdykehm", "pzkxvagk", "wvngpttoj", "mkbm"};
  ASSERT_EQ("tf", business_tasks(data, 17));
}
TEST(TEST_NAME, Extended21)
{
  auto data = std::vector<std::string>{"cwptj", "umr", "vev", "ko", "sxqyo", "bkj", "aj"};
  ASSERT_EQ("umr", business_tasks(data, 532));
}
TEST(TEST_NAME, Extended22)
{
  auto data = std::vector<std::string>{"a", "b"};
  ASSERT_EQ("b", business_tasks(data, 1));
}
TEST(TEST_NAME, Extended23)
{
  auto data = std::vector<std::string>{"blhrqkjb", "amdx", "czrg", "rjtlrkk", "ot", "qe", "qhztfnb", "dqtq", "jacbegc", "v", "xfrbmc", "cferlfdon", "jzxoy", "oqodwdohkp", "fvuuzhbmc", "wqax", "ubikflhdfc", "fvfdirmmts", "r", "yognjjwm", "qzihgkc", "rzl", "vzhnvebph", "gmzn", "xjcixrv", "pxmg", "slhfh", "iyoryw", "ywfto", "xmq", "trwou", "gbchxg", "uyarlnculn", "lbrovr", "spqeqhq", "daj", "ns", "eaypuhvepk", "cndcgx", "hqgihacbep", "njdykehm", "pzkxvagk", "wvngpttoj", "mkbm"};
  ASSERT_EQ("vzhnvebph", business_tasks(data, 1000));
}
TEST(TEST_NAME, Extended24)
{
  auto data = std::vector<std::string>{"zlqamum", "yjsrpybmq", "tjllfea", "fxjqzznvg", "nvhekxr", "am", "skmazcey", "piklp", "olcqvhg", "dnpo", "bhcfc", "y", "h", "fj", "bjeoaxglt", "oafduixsz", "kmtbaxu", "qgcxjbfx", "my", "mlhy", "bt", "bo", "q"};
  ASSERT_EQ("fxjqzznvg", business_tasks(data, 9000000));
}
TEST(TEST_NAME, Extended25)
{
  auto data = std::vector<std::string>{"zlqamum", "a", "a", "fxjqzznvg", "nvhekxr", "am", "skmazcey", "piklp", "olcqvhg", "dnpo", "bhcfc", "y", "h", "fj", "bjeoaxglt", "oafduixsz", "kmtbaxu", "qgcxjbfx", "my", "mlhy", "bt", "bo", "q"};
  ASSERT_EQ("fxjqzznvg", business_tasks(data, 9000000));
}
TEST(TEST_NAME, Extended26)
{
  auto data = std::vector<std::string>{"zlqamum", "a", "a", "a", "nvhekxr", "am", "skmazcey", "piklp", "olcqvhg", "dnpo", "bhcfc", "y", "h", "fj", "bjeoaxglt", "oafduixsz", "kmtbaxu", "qgcxjbfx", "my", "mlhy", "bt", "bo", "q"};
  ASSERT_EQ("am", business_tasks(data, 9000001));
}
TEST(TEST_NAME, Extended27)
{
  auto data = std::vector<std::string>{"a", "b", "c", "d", "e", "f", "g", "u", "er", "fi", "ao", "diu", "foiu", "vlue", "lqdu", "lfai", "piud", "a", "fivu", "voiu", "vlzakejv", "efliu", "sqldf", "ouef", "lakfjoiu", "xocvui", "faoiufa", "mvoiuv", "azoeiufnv", "aozefuv", "oiuafze", "voiqsdu", "falj", "faoiub", "dflkj", "baozif", "faljkf", "ljfal", "falkj", "faljk", "blkcj", "fdajoij", "faljk", "falkjb", "fajlkzef", "jlkaf", "falj", "falkjf", "ljkfa", "ljkfd"};
  ASSERT_EQ("ao", business_tasks(data, 9997997));
}
TEST(TEST_NAME, Extended28)
{
  auto data = std::vector<std::string>{"zlqamum", "yjsrpybmq", "tjllfea", "fxjqzznvg", "nvhekxr", "am", "skmazcey", "piklp", "olcqvhg", "dnpo", "bhcfc", "y", "h", "fj", "bjeoaxglt", "oafduixsz", "kmtbaxu", "qgcxjbfx", "my", "mlhy", "bt", "bo", "q"};
  ASSERT_EQ("y", business_tasks(data, 10000000));
}
TEST(TEST_NAME, Extended29)
{
  auto data = std::vector<std::string>{"a", "s", "d", "g", "h"};
  ASSERT_EQ("g", business_tasks(data, 17));
}
TEST(TEST_NAME, Extended30)
{
  auto data = std::vector<std::string>{"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "aa", "bb", "cc", "dd", "ee", "ff", "gg", "hh", "ii", "jj", "kk", "ll", "mm", "nn", "oo", "pp", "qq", "rr", "ss", "tt", "uu", "vv", "ww", "xx"};
  ASSERT_EQ("w", business_tasks(data, 10000000));
}
TEST(TEST_NAME, Extended31)
{
  auto data = std::vector<std::string>{"a", "b", "c", "d"};
  ASSERT_EQ("b", business_tasks(data, 7));
}
TEST(TEST_NAME, Extended32)
{
  auto data = std::vector<std::string>{"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "w", "v", "x", "y", "aa", "bb", "cc", "dd", "ee", "ff", "gg", "hh", "ii", "jj", "kk", "ll", "mm", "nn", "oo", "pp", "qq", "rr", "ss", "tt", "uu", "ww", "vv", "xx"};
  ASSERT_EQ("gg", business_tasks(data, 9999993));
}
TEST(TEST_NAME, Extended33)
{
  auto data = std::vector<std::string>{"a", "deleted"};
  ASSERT_EQ("deleted", business_tasks(data, 1));
}
TEST(TEST_NAME, Extended34)
{
  auto data = std::vector<std::string>{"a", "b", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "s", "d", "f", "g", "h", "j", "k", "l", "z", "x", "v", "n", "m", "aq", "aw", "ae", "ar", "at", "ay", "au", "ai", "ao", "as", "af", "ag", "ah", "aj", "ak", "al", "az", "ax", "ac", "ava", "ab", "an", "am", "appp", "ajk"};
  ASSERT_EQ("v", business_tasks(data, 10000000));
}
TEST(TEST_NAME, Extended35)
{
  auto data = std::vector<std::string>{"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "aa", "bb", "cc", "dd", "ee", "ff", "gg", "hh", "ii", "jj", "kk", "ll", "mm", "nn", "oo", "pp", "qq", "rr", "ss", "tt", "uu", "vv", "ww", "xx"};
  ASSERT_EQ("w", business_tasks(data, 10000000));
}
TEST(TEST_NAME, Extended36)
{
  auto data = std::vector<std::string>{"a", "b", "c", "d"};
  ASSERT_EQ("b", business_tasks(data, 100999));
}
TEST(TEST_NAME, Extended37)
{
  auto data = std::vector<std::string>{"zlqamum", "yjsrpybmq", "tjllfea", "fxjqzznvg", "nvhekxr", "am", "skmazcey", "piklp", "olcqvhg", "dnpo", "bhcfc", "y", "h", "fj", "bjeoaxglt", "oafduixsz", "kmtbaxu", "qgcxjbfx", "my", "mlhy", "bt", "bo", "q"};
  ASSERT_EQ("fxjqzznvg", business_tasks(data, 9000000));
}
TEST(TEST_NAME, Extended38)
{
  auto data = std::vector<std::string>{"zlqamum", "a", "a", "fxjqzznvg", "nvhekxr", "am", "skmazcey", "piklp", "olcqvhg", "dnpo", "bhcfc", "y", "h", "fj", "bjeoaxglt", "oafduixsz", "kmtbaxu", "qgcxjbfx", "my", "mlhy", "bt", "bo", "q"};
  ASSERT_EQ("fxjqzznvg", business_tasks(data, 9000000));
}
TEST(TEST_NAME, Extended39)
{
  auto data = std::vector<std::string>{"zlqamum", "a", "a", "a", "nvhekxr", "am", "skmazcey", "piklp", "olcqvhg", "dnpo", "bhcfc", "y", "h", "fj", "bjeoaxglt", "oafduixsz", "kmtbaxu", "qgcxjbfx", "my", "mlhy", "bt", "bo", "q"};
  ASSERT_EQ("am", business_tasks(data, 9000001));
}
TEST(TEST_NAME, Extended40)
{
  auto data = std::vector<std::string>{"a", "b", "c", "d", "e", "f", "g", "u", "er", "fi", "ao", "diu", "foiu", "vlue", "lqdu", "lfai", "piud", "a", "fivu", "voiu", "vlzakejv", "efliu", "sqldf", "ouef", "lakfjoiu", "xocvui", "faoiufa", "mvoiuv", "azoeiufnv", "aozefuv", "oiuafze", "voiqsdu", "falj", "faoiub", "dflkj", "baozif", "faljkf", "ljfal", "falkj", "faljk", "blkcj", "fdajoij", "faljk", "falkjb", "fajlkzef", "jlkaf", "falj", "falkjf", "ljkfa", "ljkfd"};
  ASSERT_EQ("ao", business_tasks(data, 9997997));
}
TEST(TEST_NAME, Extended41)
{
  auto data = std::vector<std::string>{"zlqamum", "yjsrpybmq", "tjllfea", "fxjqzznvg", "nvhekxr", "am", "skmazcey", "piklp", "olcqvhg", "dnpo", "bhcfc", "y", "h", "fj", "bjeoaxglt", "oafduixsz", "kmtbaxu", "qgcxjbfx", "my", "mlhy", "bt", "bo", "q"};
  ASSERT_EQ("y", business_tasks(data, 10000000));
}
TEST(TEST_NAME, Extended42)
{
  auto data = std::vector<std::string>{"a", "s", "d", "g", "h"};
  ASSERT_EQ("g", business_tasks(data, 17));
}
TEST(TEST_NAME, Extended43)
{
  auto data = std::vector<std::string>{"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "aa", "bb", "cc", "dd", "ee", "ff", "gg", "hh", "ii", "jj", "kk", "ll", "mm", "nn", "oo", "pp", "qq", "rr", "ss", "tt", "uu", "vv", "ww", "xx"};
  ASSERT_EQ("w", business_tasks(data, 10000000));
}
TEST(TEST_NAME, Extended44)
{
  auto data = std::vector<std::string>{"a", "b", "c", "d"};
  ASSERT_EQ("b", business_tasks(data, 7));
}
TEST(TEST_NAME, Extended45)
{
  auto data = std::vector<std::string>{"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "w", "v", "x", "y", "aa", "bb", "cc", "dd", "ee", "ff", "gg", "hh", "ii", "jj", "kk", "ll", "mm", "nn", "oo", "pp", "qq", "rr", "ss", "tt", "uu", "ww", "vv", "xx"};
  ASSERT_EQ("gg", business_tasks(data, 9999993));
}
TEST(TEST_NAME, Extended46)
{
  auto data = std::vector<std::string>{"a", "deleted"};
  ASSERT_EQ("deleted", business_tasks(data, 1));
}
TEST(TEST_NAME, Extended47)
{
  auto data = std::vector<std::string>{"a", "b", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "s", "d", "f", "g", "h", "j", "k", "l", "z", "x", "v", "n", "m", "aq", "aw", "ae", "ar", "at", "ay", "au", "ai", "ao", "as", "af", "ag", "ah", "aj", "ak", "al", "az", "ax", "ac", "ava", "ab", "an", "am", "appp", "ajk"};
  ASSERT_EQ("v", business_tasks(data, 10000000));
}
TEST(TEST_NAME, Extended48)
{
  auto data = std::vector<std::string>{"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "aa", "bb", "cc", "dd", "ee", "ff", "gg", "hh", "ii", "jj", "kk", "ll", "mm", "nn", "oo", "pp", "qq", "rr", "ss", "tt", "uu", "vv", "ww", "xx"};
  ASSERT_EQ("w", business_tasks(data, 10000000));
}
TEST(TEST_NAME, Extended49)
{
  auto data = std::vector<std::string>{"a", "b", "c", "d"};
  ASSERT_EQ("b", business_tasks(data, 100999));
}
TEST(TEST_NAME, Extended50)
{
  auto data = std::vector<std::string>{"zlqamum", "yjsrpybmq", "tjllfea", "fxjqzznvg", "nvhekxr", "am", "skmazcey", "piklp", "olcqvhg", "dnpo", "bhcfc", "y", "h", "fj", "bjeoaxglt", "oafduixsz", "kmtbaxu", "qgcxjbfx", "my", "mlhy", "bt", "bo", "q"};
  ASSERT_EQ("fxjqzznvg", business_tasks(data, 9000000));
}
TEST(TEST_NAME, Extended51)
{
  auto data = std::vector<std::string>{"zlqamum", "a", "a", "fxjqzznvg", "nvhekxr", "am", "skmazcey", "piklp", "olcqvhg", "dnpo", "bhcfc", "y", "h", "fj", "bjeoaxglt", "oafduixsz", "kmtbaxu", "qgcxjbfx", "my", "mlhy", "bt", "bo", "q"};
  ASSERT_EQ("fxjqzznvg", business_tasks(data, 9000000));
}
TEST(TEST_NAME, Extended52)
{
  auto data = std::vector<std::string>{"zlqamum", "a", "a", "a", "nvhekxr", "am", "skmazcey", "piklp", "olcqvhg", "dnpo", "bhcfc", "y", "h", "fj", "bjeoaxglt", "oafduixsz", "kmtbaxu", "qgcxjbfx", "my", "mlhy", "bt", "bo", "q"};
  ASSERT_EQ("am", business_tasks(data, 9000001));
}
TEST(TEST_NAME, Extended53)
{
  auto data = std::vector<std::string>{"a", "b", "c", "d", "e", "f", "g", "u", "er", "fi", "ao", "diu", "foiu", "vlue", "lqdu", "lfai", "piud", "a", "fivu", "voiu", "vlzakejv", "efliu", "sqldf", "ouef", "lakfjoiu", "xocvui", "faoiufa", "mvoiuv", "azoeiufnv", "aozefuv", "oiuafze", "voiqsdu", "falj", "faoiub", "dflkj", "baozif", "faljkf", "ljfal", "falkj", "faljk", "blkcj", "fdajoij", "faljk", "falkjb", "fajlkzef", "jlkaf", "falj", "falkjf", "ljkfa", "ljkfd"};
  ASSERT_EQ("ao", business_tasks(data, 9997997));
}
TEST(TEST_NAME, Extended54)
{
  auto data = std::vector<std::string>{"zlqamum", "yjsrpybmq", "tjllfea", "fxjqzznvg", "nvhekxr", "am", "skmazcey", "piklp", "olcqvhg", "dnpo", "bhcfc", "y", "h", "fj", "bjeoaxglt", "oafduixsz", "kmtbaxu", "qgcxjbfx", "my", "mlhy", "bt", "bo", "q"};
  ASSERT_EQ("y", business_tasks(data, 10000000));
}
TEST(TEST_NAME, Extended55)
{
  auto data = std::vector<std::string>{"a", "s", "d", "g", "h"};
  ASSERT_EQ("g", business_tasks(data, 17));
}
TEST(TEST_NAME, Extended56)
{
  auto data = std::vector<std::string>{"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "aa", "bb", "cc", "dd", "ee", "ff", "gg", "hh", "ii", "jj", "kk", "ll", "mm", "nn", "oo", "pp", "qq", "rr", "ss", "tt", "uu", "vv", "ww", "xx"};
  ASSERT_EQ("w", business_tasks(data, 10000000));
}
TEST(TEST_NAME, Extended57)
{
  auto data = std::vector<std::string>{"a", "b", "c", "d"};
  ASSERT_EQ("b", business_tasks(data, 7));
}
TEST(TEST_NAME, Extended58)
{
  auto data = std::vector<std::string>{"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "w", "v", "x", "y", "aa", "bb", "cc", "dd", "ee", "ff", "gg", "hh", "ii", "jj", "kk", "ll", "mm", "nn", "oo", "pp", "qq", "rr", "ss", "tt", "uu", "ww", "vv", "xx"};
  ASSERT_EQ("gg", business_tasks(data, 9999993));
}
TEST(TEST_NAME, Extended59)
{
  auto data = std::vector<std::string>{"a", "deleted"};
  ASSERT_EQ("deleted", business_tasks(data, 1));
}
TEST(TEST_NAME, Extended60)
{
  auto data = std::vector<std::string>{"a", "b", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "s", "d", "f", "g", "h", "j", "k", "l", "z", "x", "v", "n", "m", "aq", "aw", "ae", "ar", "at", "ay", "au", "ai", "ao", "as", "af", "ag", "ah", "aj", "ak", "al", "az", "ax", "ac", "ava", "ab", "an", "am", "appp", "ajk"};
  ASSERT_EQ("v", business_tasks(data, 10000000));
}
TEST(TEST_NAME, Extended61)
{
  auto data = std::vector<std::string>{"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "aa", "bb", "cc", "dd", "ee", "ff", "gg", "hh", "ii", "jj", "kk", "ll", "mm", "nn", "oo", "pp", "qq", "rr", "ss", "tt", "uu", "vv", "ww", "xx"};
  ASSERT_EQ("w", business_tasks(data, 10000000));
}
TEST(TEST_NAME, Extended62)
{
  auto data = std::vector<std::string>{"a", "b", "c", "d"};
  ASSERT_EQ("b", business_tasks(data, 100999));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}
