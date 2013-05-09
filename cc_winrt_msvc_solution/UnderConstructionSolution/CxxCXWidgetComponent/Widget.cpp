namespace CxxCXWidgetComponent
{
    public ref class Widget sealed
    {
    public:
    
        Widget()           : _number(0)      { }
        Widget(int number) : _number(number) { }
    
        int GetNumber() { return _number; }
    
    private:
        int _number;
    };
}
