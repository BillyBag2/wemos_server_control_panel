/*
 * class TempString.
 * A teporary string.
 */
class TempString {
  public:
    char * string;
    TempString(char * a,char * b);
    TempString(char * a,char * b, char * c);
    /*
     * purge()
     * Finish with string while still in scope.
     * Cannot be used after this.
     */
    void purge();
    ~TempString();
};
