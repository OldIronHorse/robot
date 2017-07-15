#define CMD_BUFFER_LENGTH 10

class Commands{
  public:
    enum Verb {NONE, FORWARD, BACKWARD, RIGHT, LEFT, STOP, SCAN};
    
    void init(int speed);
    void read();

    Verb _verb;
    int _arg;

    char _cmd_buffer[CMD_BUFFER_LENGTH];
    int _cmd_buffer_next;
};
