// The following tests validate the parser and emitter together
#include <gtest/gtest.h>
#include "vb2c/emitter.h"
#include "vb2c/parser.h"

TEST(EmitterTest, Average)
{
    const std::string source = R"(
# Compute average of given values

LET a    = 0
WHILE   a < 1 REPEAT
    PRINT "Enter number of scores: "
    INPUT   a
  ENDWHILE

LET b = 0
LET s =  0
 PRINT "Enter one value at a time: "
WHILE b < a   REPEAT
    INPUT c
    LET s = s + c
    LET b =   b + 1
ENDWHILE

PRINT   "Average: "
PRINT s / a

)";

    lexer lexer(source);
    emitter emitter("");
    parser parser(lexer, emitter);

    parser.program();

    const std::string expected = R"(#include <stdio.h>
#include <stdlib.h>
int main(void){
float a;
float b;
float s;
float c;
a=0;
while(a<1){
printf("Enter number of scores: \n");
if(scanf("%f",&a)==EOF){
printf("Error: Invalid input\n");
exit(EXIT_FAILURE);
}
}
b=0;
s=0;
printf("Enter one value at a time: \n");
while(b<a){
if(scanf("%f",&c)==EOF){
printf("Error: Invalid input\n");
exit(EXIT_FAILURE);
}
s=s+c;
b=b+1;
}
printf("Average: \n");
printf("%.2f\n",s/a);
return EXIT_SUCCESS;
}
)";

    EXPECT_EQ(emitter.get_combined(), expected);
}

TEST(EmitterTest, Fibonacci)
{
    const std::string source = R"(
PRINT "How many fibonacci numbers do you want?"


   INPUT nums
PRINT ""

 LET a = 0
LET b = 1

WHILE     nums > 0 REPEAT
    PRINT a

    LET c = a + b
    LET a = b
    LET b =   c
    LET   nums = nums - 1
  ENDWHILE
)";

    lexer lexer(source);
    emitter emitter("");
    parser parser(lexer, emitter);

    parser.program();

    const std::string expected = R"(#include <stdio.h>
#include <stdlib.h>
int main(void){
float nums;
float a;
float b;
float c;
printf("How many fibonacci numbers do you want?\n");
if(scanf("%f",&nums)==EOF){
printf("Error: Invalid input\n");
exit(EXIT_FAILURE);
}
printf("\n");
a=0;
b=1;
while(nums>0){
printf("%.2f\n",a);
c=a+b;
a=b;
b=c;
nums=nums-1;
}
return EXIT_SUCCESS;
}
)";

    EXPECT_EQ(emitter.get_combined(), expected);
}

TEST(EmitterTest, Goto)
{
    const std::string source = R"(


IF 6 < 9 THEN
    GOTO less_than
    IF 6 > 9 THEN
GOTO greater_than
    ENDIF
ENDIF

  PRINT "6 is equal to 9"
GOTO    end # Prevent the other print statements from executing

LABEL greater_than

PRINT "6 is greater than 9"
 GOTO end

LABEL less_than
PRINT "6 is less than 9"
LABEL       end
)";

    lexer lexer(source);
    emitter emitter("");
    parser parser(lexer, emitter);

    parser.program();

    const std::string expected = R"(#include <stdio.h>
#include <stdlib.h>
int main(void){
if(6<9){
goto less_than;
if(6>9){
goto greater_than;
}
}
printf("6 is equal to 9\n");
goto end;
greater_than:
printf("6 is greater than 9\n");
goto end;
less_than:
printf("6 is less than 9\n");
end:
return EXIT_SUCCESS;
}
)";

    EXPECT_EQ(emitter.get_combined(), expected);
}

TEST(EmitterTest, NoStdio)
{
    const std::string source = R"(
LET   a =     -5 + 2
 LET b = 3 * 4

#   This should be 9.0
LET ___sum =     a + b
)";

    lexer lexer(source);
    emitter emitter("");
    parser parser(lexer, emitter);

    parser.program();

    const std::string expected = R"(#include <stdlib.h>
int main(void){
float a;
float b;
float ___sum;
a=-5+2;
b=3*4;
___sum=a+b;
return EXIT_SUCCESS;
}
)";

    EXPECT_EQ(emitter.get_combined(), expected);
}
