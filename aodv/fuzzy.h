class fuzzy
{
  public:
    
    float fuzzify(unsigned int a, unsigned int b, unsigned int c);
    float defuzzify(float vl, float l,float m, float h, float vh);
    float mem_fnc(float x,float a,float b,float c,float d);
    float mem_fnc2(float x, float a, float b);
    float maxf(float temp1, float temp2, float temp3);
    float minf(float temp1, float temp2, float temp3);
};