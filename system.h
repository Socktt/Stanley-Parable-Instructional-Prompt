void * memset(void *dest, int c, int n);
char* itoa(int value, char* result, int base);
void strcpy(char start[], char dest[], int n);
int strcmp(char a[], char b[]);

struct regs
{
    unsigned int gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
};

void irq_install();
void irq_install_handler(int irq, void (*handler)(struct regs *r));
void irq_uninstall_handler(int irq);
void timer_install();
void timer_phase(int hz);
void sleep(int ms);
void keyboard_install();
void mouse_install();
int getTimerVal();