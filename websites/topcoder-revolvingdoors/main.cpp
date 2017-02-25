#include "gtest/gtest.h"

#include <string>
#include <vector>

#include SPECIFIC_HEADER

// Running tests

TEST(TEST_NAME, Example0)
{
  auto map = std::vector<std::string>{
      "    ### ",
      "    #E# ",
      "   ## # ",
      "####  ##",
      "# S -O-#",
      "# ###  #",
      "#      #",
      "########"
  };
  ASSERT_EQ(2, turns(map));
}
TEST(TEST_NAME, Example1)
{
  auto map = std::vector<std::string>{
      "#### ",
      "#S|##",
      "# O #",
      "##|E#",
      " ####"
  };
  ASSERT_EQ(-1, turns(map));
}
TEST(TEST_NAME, Example2)
{
  auto map = std::vector<std::string>{
      " |  |  |     |  |  |  |  |  | ",
      " O  O EO -O- O  O  O  O  OS O ",
      " |  |  |     |  |  |  |  |  | "
  };
  ASSERT_EQ(7, turns(map));
}
TEST(TEST_NAME, Example3)
{
  auto map = std::vector<std::string>{
      "###########",
      "#    #    #",
      "#  S | E  #",
      "#    O    #",
      "#    |    #",
      "#         #",
      "###########"
  };
  ASSERT_EQ(0, turns(map));
}
TEST(TEST_NAME, Example4)
{
  auto map = std::vector<std::string>{
      "        E",
      "    |    ",
      "    O    ",
      "    |    ",
      " -O-S-O- ",
      "    |    ",
      "    O    ",
      "    |    ",
      "         "
  };
  ASSERT_EQ(-1, turns(map));
}
TEST(TEST_NAME, Example5)
{
  auto map = std::vector<std::string>{
      "##E#   ",
      "#  ##  ",
      " -O-## ",
      " #  ## ",
      " ##  ##",
      "  -O-  ",
      "##  ## ",
      " # ### ",
      " #  S  "
  };
  ASSERT_EQ(5, turns(map));
}
TEST(TEST_NAME, Example6)
{
  auto map = std::vector<std::string>{
      "#############",
      "#  #|##|#   #",
      "#   O  O    #",
      "# E || || S #",
      "#    O  O   #",
      "#   #|##|#  #",
      "#############"
  };
  ASSERT_EQ(4, turns(map));
}

TEST(TEST_NAME, Extended0)
{
  auto map = std::vector<std::string>{"########", "#    | #", "#S   O #", "#-O- | #", "#E  #  #", "#      #", "########"};
  ASSERT_EQ(1, turns(map));
}
TEST(TEST_NAME, Extended1)
{
  auto map = std::vector<std::string>{"    #   ", " #### # ", "##|  |# ", "E O  O  ", "# |##|  ", "##      ", " #S     "};
  ASSERT_EQ(3, turns(map));
}
TEST(TEST_NAME, Extended2)
{
  auto map = std::vector<std::string>{"        ### ", "     #### ##", " ### #  -O-#", " #E### #   #", "##  ##| #  #", "#-O-  O   ##", "#  ## |## # ", "# #### # |##", "#     S  O #", "#########|##", "        ### "};
  ASSERT_EQ(8, turns(map));
}
TEST(TEST_NAME, Extended3)
{
  auto map = std::vector<std::string>{" #### S | ", "##|  |# O ", "E O  O #| ", "# |##|    ", "##    ####"};
  ASSERT_EQ(7, turns(map));
}
TEST(TEST_NAME, Extended4)
{
  auto map = std::vector<std::string>{"S                   |   |    #                    ", "                    O   O    #                    ", "                    |   |    #                    ", "                     -O- -O-##                    ", "                    #   |    #                    ", "                    #   O -O-#                    ", "                    #   |    #                    ", "##########################   #                    ", "                          -O-                     ", "                                                  ", "                                                  ", "                   -O-                            ", "###################   ############################", "                  #   #                           ", "                  #-O-#                           ", "                  #   #                           ", "                 ##   #                           ", "                 # | #                            ", "                 # O #                            ", "                 # |##                            ", "                 ## #                             ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                 E"};
  ASSERT_EQ(9, turns(map));
}
TEST(TEST_NAME, Extended5)
{
  auto map = std::vector<std::string>{"S                                                 ", "###############################   ################", "                             ##   #               ", "                             # | #                ", "                             # O #                ", "                             # |##                ", "                             ## #                 ", "                            # | #                 ", "                            # O #                 ", "                            # |##                 ", "                            ## #                  ", "                           # | #                  ", "                           # O #                  ", "                           # |##                  ", "                           ## #                   ", "                          # | #                   ", "                          # O #                   ", "                          # |##                   ", "                          ## #                    ", "                         # | #                    ", "                         # O #                    ", "                         # |##                    ", "                         ## #                     ", "                        # | #                     ", "                        # O #                     ", "                        # |##                     ", "                        ## #                      ", "                       # | #                      ", "                       # O #                      ", "                       # |##                      ", "                       ## #                       ", "                      # | #                       ", "                      # O #                       ", "                      # |##                       ", "                      ## #                        ", "                     # | #                        ", "                     # O #                        ", "                     # |##                        ", "                     ## #                         ", "                    # | #                         ", "                    # O #                         ", "                    # |##                         ", "                    ## #                          ", "                                                  ", "                                                 E"};
  ASSERT_EQ(30, turns(map));
}
TEST(TEST_NAME, Extended6)
{
  auto map = std::vector<std::string>{"                  ", "                  ", "       ########   ", "       #     S#   ", "       #   ## #   ", "       #  # | #   ", "      ##  # O #   ", "      #E|## |##   ", "      # O ## #    ", "       #|    #    ", "       #######    ", "                  ", "                  "};
  ASSERT_EQ(6, turns(map));
}
TEST(TEST_NAME, Extended7)
{
  auto map = std::vector<std::string>{"       ##########E #     ", "       #     S   -O-     ", "       #   ## # ##       ", "       #  # | # #        ", "    ####  # O # #        ", "    #   |## |## #        ", "    #   O ## ## #   #####", "    #  #|     # #   #    ", "    #  ##  #### ##  #  # ", "    #    #|  ##|  #  |## ", "    #     O  # O  #  O # ", "    #     |#   |# ###| # ", "    #      #    #      # ", "    ######### ########## ", "            #            "};
  ASSERT_EQ(18, turns(map));
}
TEST(TEST_NAME, Extended8)
{
  auto map = std::vector<std::string>{"###################################", "#S                                #", "# ## ##### ##### ##### #####  ##  #", "### |##|  |##|  |##|  |##|  |## | #", "#E  O  O  O  O  O  O  O  O  O # O #", "####|  |##|  |##|  |##|  |##| # |##", "   #  #     #     #     #     ## # ", "   ##########################    # ", "                            ###### "};
  ASSERT_EQ(31, turns(map));
}
TEST(TEST_NAME, Extended9)
{
  auto map = std::vector<std::string>{"S                            ", "####### ####### ####### ###  ", " #   |# ##   |# ##   |# ## | ", " #|  O |##|  O |##|  O |## O ", " EO  | O  O  | O  O  | O # |#", "  |####|  |####|  |####| ## #", "## #  #### #  ####          #", " #                          #"};
  ASSERT_EQ(40, turns(map));
}
TEST(TEST_NAME, Extended10)
{
  auto map = std::vector<std::string>{"S                            ", "####### ####### ####### ###  ", "E#   |# ##   |# ##   |# ##   ", " #|  O |##|  O |##|  O |##   ", "  O  | O  O  | O  O  | O #  #", "  |####|  |####|  |####| ## #", "## #  #### #  ####          #", " #                          #"};
  ASSERT_EQ(24, turns(map));
}
TEST(TEST_NAME, Extended11)
{
  auto map = std::vector<std::string>{"S                    |   |   #                    ", "                     O   O   #                    ", "                     |   |   #                    ", "                     -O- -O-##                    ", "                    #  |     #                    ", "                    #  O  -O-#                    ", "                    #  |-O-  #                    ", "#########################    #                    ", "                         #-O-                     ", "                                                  ", "                                                  ", "                                                  ", "###################   ############################", "                  #   #                           ", "                  #-O-#                           ", "                  #   #                           ", "                 ##   #                           ", "                 # | #                            ", "                 # O #                            ", "                 # |##                            ", "                 ## #                             ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                 E"};
  ASSERT_EQ(7, turns(map));
}
TEST(TEST_NAME, Extended12)
{
  auto map = std::vector<std::string>{"    S     ", "-O--O--O-#", "          ", "#-O--O--O-", "          ", "-O--O--O-#", "    E     "};
  ASSERT_EQ(3, turns(map));
}
TEST(TEST_NAME, Extended13)
{
  auto map = std::vector<std::string>{"    ########", "    # |    #", "##### O    #", "# |   |    #", "#SO #### E #", "# |   |    #", "##### O    #", "    # |    #", "    ########"};
  ASSERT_EQ(2, turns(map));
}
TEST(TEST_NAME, Extended14)
{
  auto map = std::vector<std::string>{"  #       ", "   -O- |  ", "-O-    O  ", "   |-O-|  ", "   O   -O-", " S |   |  ", " |     O  ", " O  -O-|  ", " |-O-     ", "         E"};
  ASSERT_EQ(0, turns(map));
}
TEST(TEST_NAME, Extended15)
{
  auto map = std::vector<std::string>{" | ", " OE", "S|#"};
  ASSERT_EQ(2, turns(map));
}
TEST(TEST_NAME, Extended16)
{
  auto map = std::vector<std::string>{" | ", " OS", "E|#"};
  ASSERT_EQ(2, turns(map));
}
TEST(TEST_NAME, Extended17)
{
  auto map = std::vector<std::string>{"######## ###", "    # #-O-|E", " # #-O-|  O ", "#-O-|  O  |#", "#|  O  |-O-#", " O  |-O-# # ", "S|-O-# #    ", "### ########"};
  ASSERT_EQ(-1, turns(map));
}
TEST(TEST_NAME, Extended18)
{
  auto map = std::vector<std::string>{"######## ###", "    # #-O-|E", " # #-O-|  O ", "#-O-|  O  |#", " |  O  |-O-#", " O  |-O-# # ", "S|-O-# #    ", "### ########"};
  ASSERT_EQ(7, turns(map));
}
TEST(TEST_NAME, Extended19)
{
  auto map = std::vector<std::string>{"S                                                 ", "###############################   # ##############", "                             ##   #| #            ", "                             # | # O              ", "                             # O # |#             ", "                             # |##  #             ", "                             ## #   #             ", "                            # | #   #             ", "                            # O #   #             ", "                            # |##   #             ", "                            ## #    #             ", "                           # | #    #             ", "                           # O #    #             ", "                           # |##    #             ", "                           ## #     #             ", "                          # | #     #             ", "                          # O #     #             ", "                          # |##     #             ", "                          ## #      #             ", "                         # | #      #             ", "                         # O #      #             ", "                         # |##      #             ", "                         ## #       #             ", "                        # | #       #             ", "                        # O #       #             ", "                        # |##       #             ", "                        ## #        #             ", "                       # | #        #             ", "                       # O #        #             ", "                       # |##        #             ", "                       ## #         #             ", "                      # | #         #             ", "                      # O #         #             ", "                      # |##         #             ", "                      ## #          #             ", "                     # | #          #             ", "                     # O #          #             ", "                     # |##          #             ", "                     ## #           #             ", "                      #             #             ", "                      ###############             ", "                                                  ", "                                                  ", "                                                  ", "                                                 E"};
  ASSERT_EQ(47, turns(map));
}
TEST(TEST_NAME, Extended20)
{
  auto map = std::vector<std::string>{"S                                                 ", "###############################   # ##############", "                             ##   #| #            ", "                             #   # O              ", "                             #   # |#             ", "                             #  ##  # |###########", "                             ## #   # O           ", "                            # | #   ##|           ", "                            # O #      #          ", "                            # |##   ####          ", "                            ## #    #             ", "                           # | #    #             ", "                           # O #    #             ", "                           # |##    #             ", "                           ## #     #             ", "                          # | #     #             ", "                          # O #     #             ", "                          # |##     #             ", "                          ## #      #             ", "                         # | #      #             ", "                         # O #      #             ", "                         # |##      #             ", "                         ## #       #             ", "                        # | #       #             ", "                        # O #       #             ", "                        # |##       #             ", "                        ## #        #             ", "                       # | #        #             ", "                       # O #        #             ", "                       # |##        #             ", "                       ## #         #             ", "                      # | #         #             ", "                      # O #         #             ", "                      # |##         #             ", "                      ## #          #             ", "                     # | #          #             ", "                     # O #          #             ", "                     # |##          #             ", "                     ## #           #             ", "                      #             #             ", "                      ###############             ", "                                                  ", "                                                  ", "                                                  ", "                                                 E"};
  ASSERT_EQ(60, turns(map));
}
TEST(TEST_NAME, Extended21)
{
  auto map = std::vector<std::string>{"S                                                 ", "############################   # ######           ", "                          ##   #| #   #           ", "                          #   # O     #           ", "                          #   # |#  ###           ", "                          #  ##  # |##### ########", "                          ## #   # O    #| #      ", "                         #   #   ##| #   O        ", "                         #   #      ###  |#  |####", "                         #  ##   ####  ####  O    ", "                         ## #    #        ###| ## ", "                        #   #    #        #   ### ", "                        #   #                   # ", "                        #  ##    ################ ", "                        ## #     #                ", "                       # | #     #                ", "                       # O #     #                ", "                       # |##     #                ", "                       ## #      #                ", "                      # | #      #                ", "                      # O #      #                ", "                      # |##      #                ", "                      ## #       #                ", "                     # | #       #                ", "                     # O #       #                ", "                     # |##       #                ", "                     ## #        #                ", "                    # | #        #                ", "                    # O #        #                ", "                    # |##        #                ", "                    ## #         #                ", "                   # | #         #                ", "                   # O #         #                ", "                   # |##         #                ", "                   ## #          #                ", "                  # | #          #                ", "                  # O #          #                ", "                  # |##          #                ", "                  ## #           #                ", "                   #             #                ", "                   ###############                ", "                                                  ", "                                                  ", "                                                  ", "                                                 E"};
  ASSERT_EQ(77, turns(map));
}
TEST(TEST_NAME, Extended22)
{
  auto map = std::vector<std::string>{"S                                                 ", "                                                  ", "                                                  ", "-O--O--O--O--O--O--O--O--O--O-                    ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                 #", "                                                #E"};
  ASSERT_EQ(-1, turns(map));
}
TEST(TEST_NAME, Extended23)
{
  auto map = std::vector<std::string>{"S                                                 ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "  -O--O--O--O--O--O--O--O--O--O-                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                 #", "                                                #E"};
  ASSERT_EQ(-1, turns(map));
}
TEST(TEST_NAME, Extended24)
{
  auto map = std::vector<std::string>{"##################################################", "#S                                               #", "#                   -O-                          #", "#                                                #", "#                                                #", "#                   -O-                          #", "#                                                #", "#                                                #", "#                                                #", "#                   -O-                          #", "#                                                #", "#                                                #", "#                                                #", "#                   -O-                          #", "#                                                #", "#                                                #", "#                   -O-                          #", "#                                                #", "#                                                #", "#                   -O-                          #", "#                                                #", "#                                                #", "#                   -O-                          #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                   -O-                          #", "#                                                #", "#                                                #", "#                   -O-                          #", "#                                                #", "#                                                #", "#                   -O-                          #", "#                                                #", "#################################################E"};
  ASSERT_EQ(-1, turns(map));
}
TEST(TEST_NAME, Extended25)
{
  auto map = std::vector<std::string>{"##################################################", "#S                                               #", "#                   -O-                          #", "#                                                #", "#                                                #", "#                   -O-                          #", "#                                                #", "#                                                #", "#                                                #", "#                   -O-                          #", "#                                                #", "#                                                #", "#                                                #", "#                   -O-                          #", "#                                                #", "#                                                #", "#                   -O-                          #", "#                                                #", "#                                                #", "#                   -O-                          #", "#                                                #", "#                                                #", "#                   -O-                          #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                   -O-                          #", "#                                                #", "#                                                #", "#                   -O-                          #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#################################################E"};
  ASSERT_EQ(-1, turns(map));
}
TEST(TEST_NAME, Extended26)
{
  auto map = std::vector<std::string>{"                                                  ", "                                                  ", " -O-                                              ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", " -O-                                              ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", " -O-                                              ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", " -O-                                              ", "                                                  ", "                                                  ", "                                                  ", "                                                S ", " -O-                                           ###", "                                               #E#", "                                               ###"};
  ASSERT_EQ(-1, turns(map));
}
TEST(TEST_NAME, Extended27)
{
  auto map = std::vector<std::string>{"                                                  ", "                                                  ", " -O-                                              ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", " -O-                                              ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", " -O-                                              ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", " -O-                                              ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", " -O-                                              ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", " -O-                                              ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", " -O-                                              ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", " -O-                                              ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", " -O-                                              ", "                                                  ", "                                                  ", "                                                  ", "                                                S ", " -O-                                           ###", "                                               #E#", "                                               ###"};
  ASSERT_EQ(-1, turns(map));
}
TEST(TEST_NAME, Extended28)
{
  auto map = std::vector<std::string>{"                                                  ", "                                                  ", " -O-                                              ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", " -O-                                              ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", " -O-                                              ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", " -O-                                              ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", " -O-                                              ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", " -O-                                              ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", " -O-                                              ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", " -O-                                              ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", " -O-                                              ", "                                                  ", "                                                  ", "                                                  ", "                                                S ", " -O-                                           ###", "                                               #E#", "                                               ###"};
  ASSERT_EQ(-1, turns(map));
}
TEST(TEST_NAME, Extended29)
{
  auto map = std::vector<std::string>{"                                                  ", "                                                  ", " -O-                                              ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", " -O-                                              ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", " -O-                                              ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", " -O-                                              ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", " -O-                                              ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", " -O-                                              ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", " -O-                                              ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", " -O-                                              ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", " -O-                                              ", "                                                  ", "                                                  ", "                                                  ", "                                                S ", " -O-                                           ###", "                                               #E#", "                                               ###"};
  ASSERT_EQ(-1, turns(map));
}
TEST(TEST_NAME, Extended30)
{
  auto map = std::vector<std::string>{"##################################################", "#S                                               #", "#                   -O-                          #", "#                                                #", "#                                                #", "#                   -O-                          #", "#                                                #", "#                                                #", "#                                                #", "#                   -O-                          #", "#                                                #", "#                                                #", "#                                                #", "#                   -O-                          #", "#                                                #", "#                                                #", "#                   -O-                          #", "#                                                #", "#                                                #", "#                   -O-                          #", "#                                                #", "#                                                #", "#                   -O-                          #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                                                #", "#                   -O-                          #", "#                                                #", "#                                                #", "#                   -O-                          #", "#                                                #", "#                                                #", "#                   -O-                          #", "#                                                #", "#################################################E"};
  ASSERT_EQ(-1, turns(map));
}
TEST(TEST_NAME, Extended31)
{
  auto map = std::vector<std::string>{"S                                                 ", "                                                  ", "                                                  ", "-O--O--O--O--O--O--O--O--O--O-                    ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                  ", "                                                 #", "                                                #E"};
  ASSERT_EQ(-1, turns(map));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret { RUN_ALL_TESTS() };
  return ret;
}

