int put_char(char code, int x, int y);
int kprintf(char *string, int x, int y);
int clear_screen();
int kprint_integer_dec(int integer, int x, int y);
int kprint_integer_hex(int integer, int x, int y);
int kprint_integer_oct(int integer, int x, int y);
int kprint_integer_bin(int integer, int x, int y);
int kprint_integer(int integer, int x, int y , int base);


int kprint_integer(int integer, int x, int y, int base){
    if(integer == 0){
        return put_char('0', x, y);
    }
    int counter = 0;
    int number = integer;
    while((number % base) != 0){
        number = number / base;
        counter++;
    }
    int i;
    number = integer;
    for(i = x + (counter - 1); i>=x; i--){
        unsigned short c = (unsigned short) number % base;
        if(c<10){
            put_char('0' + c, i, y);
        }else{
            put_char('A' + (c - 10), i, y);
        }
        number = number / base;
    }

    return 0;
}

int kprint_integer_hex(int integer, int x, int y){
    return kprint_integer(integer, x, y, 16);
}

int kprint_integer_dec(int integer, int x, int y){
    return kprint_integer(integer, x, y, 10);
}

int kprint_integer_oct(int integer, int x, int y){
    return kprint_integer(integer, x, y, 8);
}
int kprint_integer_bin(int integer, int x, int y){
    return kprint_integer(integer, x, y, 2);
}


int put_char(char code, int x, int y)
{
    unsigned char *videoram = (unsigned char *) 0xb8000;

    int pos = 80 * 2 * y + 2 * x;
    videoram[pos] = code;
    videoram[pos+1] = 0x07;

    return 0;
}

int kprintf(char* string, int x, int y)
{
    char *c;
    c = &string[0];
    while((char)*c!='\0'){
        put_char((char)*c, x++, y);
        c++;
    }

    return 0;
}

int clear_screen(){

    int i = 0;
    int j = 0;
    for(i = 0; i<30; i++)
        for(j = 0; j<80; j++)
            put_char(' ', j, i);

    return 0;
}


void kmain( void* mbd, unsigned int magic )
{
    if ( magic != 0x2BADB002 )
    {
        /* Something went not according to specs. Print an error */
        /* message and halt, but do *not* rely on the multiboot */
        /* data structure. */
    }

    /* You could either use multiboot.h */
    /* (http://www.gnu.org/software/grub/manual/multiboot/multiboot.html#multiboot_002eh) */
    /* or do your offsets yourself. The following is merely an example. */ 
    char * boot_loader_name =(char*) ((long*)mbd)[16];

    /* Print a letter to screen to see everything is working: */
    unsigned char *videoram = (unsigned char *) 0xb8000;
    clear_screen();
    kprintf("hello world",0, 4); 
    kprint_integer_dec(333, 0, 6);
    kprint_integer_hex(335, 0, 7);
    kprint_integer_hex(338, 0, 8);
    kprint_integer_bin(2, 0, 10);
    kprintf("blabla", 0, 9);
    /* Write your kernel here. */
}
