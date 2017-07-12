class SerialRover {
  public:
    SerialRover();

    void init();
    void loop();
    void read_loop();
  
  private:
    char _c;
    int _light;
};
