// int main() {
//     char ch;
//     FILE fp;
//     // open file in write mode
//     fp = fopen("std1.txt", "w");

//     printf("enter text then press ctrl d": );
//     // Till character reaches EOF, write each character in file pointer

//     while ((ch = getchar()) != EOF) {
//         putc(ch, fp);
//     }
//     fclose(fp);// close file
//     fp = fopen("std1.txt", "r");//open in read mode
//     printf("text on the file: ");
//     // Read character from file until fp equals EOF
//     while ((ch = getc(fp)) != EOF)
//     {
//         putchar(ch);//print character on console
//     }
//     fclose(fp);//close file
//     return 0;
// }
// // Ariel
