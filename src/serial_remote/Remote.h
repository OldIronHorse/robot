class Remote{
  public:
    Remote();

    void setup(int baud);
    void loop();

  private:
    char _cmd_buffer[20];
    int _next_cmd_buffer;
};
