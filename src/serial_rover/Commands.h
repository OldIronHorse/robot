class Commands{
  public:
    enum Verb {FWD, BACK, RIGHT, LEFT};

    void init(int speed);
    bool read();

    Verb _verb;
    int _arg;
};
