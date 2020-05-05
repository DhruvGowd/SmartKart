#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "table.h"


void initializeArrays(char** items, char** aisle, char** price){

    //Fruits & Vegetables
    items[0] = "apples";
    aisle[0] = "A1";
    price[0] = "$1.15/lb";

    items[1] = "oranges";
    aisle[1] = "A1";
    price[1] = "$1.39/lb";

    items[2] = "bananas";
    aisle[2] = "A1";
    price[2] = "$0.49/lb";

    items[3] = "grapefruit";
    aisle[3] = "A1";
    price[3] = "$1.25";

    items[4] = "lemons";
    aisle[4] = "A1";
    price[4] = "$2.00/lb";

    items[5] = "berries";
    aisle[5] = "A1";
    price[5] = "$2.24/lb";

    items[6] = "grapes";
    aisle[6] = "A1";
    price[6] = "$2.09/lb";

    items[7] = "plums";
    aisle[7] = "A1";
    price[7] = "$2.56/lb";

    items[8] = "avocados";
    aisle[8] = "A1";
    price[8] = "$2.10";

    items[9] = "tomatoes";
    aisle[9] = "A1";
    price[9] = "$2.66";

    items[10] = "cucumbers";
    aisle[10] = "A1";
    price[10] = "$1.99";

    items[11] = "lettuce";
    aisle[11] = "A1";
    price[11] = "$1.86";

    items[12] = "spinach";
    aisle[12] = "A1";
    price[12] = "$2.01";

    items[13] = "broccoli";
    aisle[13] = "A1";
    price[13] = "$1.80";

    items[14] = "celery";
    aisle[14] = "A1";
    price[14] = "$1.89";

    items[15] = "carrots";
    aisle[15] = "A1";
    price[15] = "$1.94";

    items[16] = "potatoes";
    aisle[16] = "A1";
    price[16] = "$5.99";

    items[17] = "mushrooms";
    aisle[17] = "A1";
    price[17] = "$7.01";

    items[18] = "cauliflower";
    aisle[18] = "A1";
    price[18] = "$2.02";


    //Meat & Fish
    items[19] = "chicken";
    aisle[19] = "B1";
    price[19] = "$4.64/lb";

    items[20] = "fish";
    aisle[20] = "B1";
    price[20] = "$7.03";

    items[21] = "shrimp";
    aisle[21] = "B1";
    price[21] = "$12.49";

    items[22] = "pork";
    aisle[22] = "B1";
    price[22] = "$3.75/lb";

    items[23] = "bacon";
    aisle[23] = "B1";
    price[23] = "$6.11/lb";

    items[24] = "beef";
    aisle[24] = "B1";
    price[24] = "$3.99/lb";

    items[25] = "turkey";
    aisle[25] = "B1";
    price[25] = "$1.51/lb";


    //Baked Goods
    items[26] = "bread";
    aisle[26] = "C1";
    price[26] = "$2.56";

    items[27] = "bagels";
    aisle[27] = "C1";
    price[27] = "$0.99/lb";

    items[28] = "donuts";
    aisle[28] = "C1";
    price[28] = "$1.02";

    items[29] = "cake";
    aisle[29] = "C1";
    price[29] = "$15.00";

    items[30] = "cookies";
    aisle[30] = "C1";
    price[30] = "$7.99";


    //Baking Staples
    items[31] = "flour";
    aisle[31] = "C2";
    price[31] = "$5.22";

    items[32] = "sugar";
    aisle[32] = "C2";
    price[32] = "$6.18";

    items[33] = "baking soda";
    aisle[33] = "C2";
    price[33] = "$3.08";

    items[34] = "baking powder";
    aisle[34] = "C2";
    price[34] = "$4.98";

    items[35] = "yeast";
    aisle[35] = "C2";
    price[35] = "$4.58";

    items[36] = "eggs";
    aisle[36] = "C2";
    price[36] = "$7.46";

    items[37] = "butter";
    aisle[37] = "C2";
    price[37] = "$5.74";

    items[38] = "chocolate chips";
    aisle[38] = "C2";
    price[38] = "$6.98";

    items[39] = "sprinkles";
    aisle[39] = "C2";
    price[39] = "$3.98";

    items[40] = "cream cheese";
    aisle[40] = "C2";
    price[40] = "$6.89";

    items[41] = "oil";
    aisle[41] = "C2";
    price[41] = "$4.44";

    items[42] = "breadcrumbs";
    aisle[42] = "C2";
    price[42] = "$8.07";


    //Canned & Jarred
    items[43] = "canned tuna";
    aisle[43] = "D1";
    price[43] = "$13.48";

    items[44] = "pickles";
    aisle[44] = "D1";
    price[44] = "$5.66";

    items[45] = "pasta sauce";
    aisle[45] = "D1";
    price[45] = "$3.98";

    items[46] = "applesauce";
    aisle[46] = "D1";
    price[46] = "$12.98";

    items[47] = "soup";
    aisle[47] = "D1";
    price[47] = "$4.96";

    items[48] = "beans";
    aisle[48] = "D1";
    price[48] = "$6.98";

    items[49] = "chili";
    aisle[49] = "D1";
    price[49] = "$5.92";


    //Frozen Foods & Drinks
    items[50] = "frozen vegetables";
    aisle[50] = "E1";
    price[50] = "$1.94";

    items[51] = "ice cream";
    aisle[51] = "E1";
    price[51] = "$4.42";

    items[52] = "veggie burgers";
    aisle[52] = "E1";
    price[52] = "$33.99";

    items[53] = "frozen meat";
    aisle[53] = "E1";
    price[53] = "$19.83";

    items[54] = "pizza";
    aisle[54] = "E1";
    price[54] = "$8.88";

    items[55] = "waffles";
    aisle[55] = "E1";
    price[55] = "$4.98";

    items[56] = "popsicles";
    aisle[56] = "E1";
    price[56] = "$5.97";

    items[57] = "juice";
    aisle[57] = "E1";
    price[57] = "$3.38";

    items[58] = "milk";
    aisle[58] = "E1";
    price[58] = "$7.02";

    items[59] = "water";
    aisle[59] = "E1";
    price[59] = "$9.98";

    items[60] = "soda";
    aisle[60] = "E1";
    price[60] = "$7.47";


    //Spices & Seasoning
    items[61] = "salt";
    aisle[61] = "F1";
    price[61] = "$5.02";

    items[62] = "pepper";
    aisle[62] = "F1";
    price[62] = "$3.98";

    items[63] = "parsley";
    aisle[63] = "F1";
    price[63] = "$5.48";

    items[64] = "paprika";
    aisle[64] = "F1";
    price[64] = "$4.58";

    items[65] = "chili powder";
    aisle[65] = "F1";
    price[65] = "$2.44";

    items[66] = "basil";
    aisle[66] = "F1";
    price[66] = "$3.83";

    items[67] = "rosemary";
    aisle[67] = "F1";
    price[67] = "$3.91";

    items[68] = "ginger";
    aisle[68] = "F1";
    price[68] = "$6.34";

    items[69] = "cinnamon";
    aisle[69] = "F1";
    price[69] = "$6.39";

    items[70] = "garlic";
    aisle[70] = "F1";
    price[70] = "$5.98";

    items[71] = "cilantro";
    aisle[71] = "F1";
    price[71] = "$3.64";


    //Sauce
    items[72] = "salad dressing";
    aisle[72] = "F2";
    price[72] = "$7.74";

    items[73] = "ketchup";
    aisle[73] = "F2";
    price[73] = "$5.98";

    items[74] = "mustard";
    aisle[74] = "F2";
    price[74] = "$6.02";

    items[75] = "relish";
    aisle[75] = "F2";
    price[75] = "$5.47";

    items[76] = "maple syrup";
    aisle[76] = "F2";
    price[76] = "$7.56";

    items[77] = "honey";
    aisle[77] = "F2";
    price[77] = "$7.93";

    items[78] = "soy sauce";
    aisle[78] = "F2";
    price[78] = "$5.02";

    items[79] = "bbq sauce";
    aisle[79] = "F2";
    price[79] = "$4.09";

    items[80] = "mayo";
    aisle[80] = "F2";
    price[80] = "$3.77";

    items[81] = "jam";
    aisle[81] = "F2";
    price[81] = "$1.98";

    items[82] = "peanut butter";
    aisle[82] = "F2";
    price[82] = "$4.68";


    //Paper Items & Cleaning Supplies
    items[83] = "paper towels";
    aisle[83] = "H1";
    price[83] = "$15.63";

    items[84] = "trash bags";
    aisle[84] = "H1";
    price[84] = "$12.87";

    items[85] = "ziploc bags";
    aisle[85] = "H1";
    price[85] = "$4.42";

    items[86] = "dishwashing soap";
    aisle[86] = "H1";
    price[86] = "$4.42";

    items[87] = "swiffer pads";
    aisle[87] = "H1";
    price[87] = "$7.97";

    items[88] = "plastic wrap";
    aisle[88] = "H1";
    price[88] = "$4.78";

    items[89] = "printer paper";
    aisle[89] = "H1";
    price[89] = "$3.97";


    //Personal Items
    items[90] = "hand soap";
    aisle[90] = "H2";
    price[90] = "$6.62";

    items[91] = "deodorant";
    aisle[91] = "H2";
    price[91] = "$5.94";

    items[92] = "shampoo";
    aisle[92] = "H2";
    price[92] = "$11.94";

    items[93] = "conditioner";
    aisle[93] = "H2";
    price[93] = "$12.02";

    items[94] = "toothbrush";
    aisle[94] = "H2";
    price[94] = "$5.43";

    items[95] = "toothpaste";
    aisle[95] = "H2";
    price[95] = "$4.47";

    items[96] = "shaving cream";
    aisle[96] = "H2";
    price[96] = "$7.47";

    items[97] = "razors";
    aisle[97] = "H2";
    price[97] = "9.97";

    items[98] = "floss";
    aisle[98] = "H2";
    price[98] = "$5.27";

    items[99] = "sunblock";
    aisle[99] = "H2";
    price[99] = "$6.48";
}


void initTable(Product* table, char** items, char** aisle, char** price){
    int i = 0;
    int ascii;

    for(i = 0; i < 100; i++){
       Product temp;
       temp.name = items[i];
       temp.location = aisle[i];
       temp.value = price[i];
       table[i] = temp;
    }
}

int getInfoIndex(Product* table, char *word){
    int index;
    for(int i = 0; i < 100; i++){
        if (strcmp(table[i].name, word) == 0){
           index = i;
        }
    }

    return index;
}

/*
int main (int argc, char * * argv){

    char *items[100];
    char *aisle[100];
    char *price[100];

    Product table [100];

    initializeArrays(items, aisle, price);

    initTable(table, items, aisle, price);

    char input [30];
    int asciiVal;
    int index;

    printf("What item do you want more info on: ");
    scanf("%s", input);
    printf("\nItem: %s\n", input);

    index = getInfoIndex(table, input);
    printf("Location: %s\n", table[index].location);
    printf("Price: %s\n", table[index].value);

}
*/
