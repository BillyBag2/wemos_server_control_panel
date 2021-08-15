/*
 * class TempString.
 * A teporary string.
 */
class TempString {
  public:
    TempString(char * a,char * b);
    TempString(char * a,char * b, char * c);
    TempString(char * a,char * b, char * c,char * d);
    TempString(char * a,char * b, char * c,char * d,char * e);
    char * s(){return string;};
    /*
     * purge()
     * Finish with string while still in scope.
     * Cannot be used after this.
     */
    void purge();
    ~TempString();
    private:
    char * string;
};
