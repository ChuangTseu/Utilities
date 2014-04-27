#ifndef TYPENAME_H
#define TYPENAME_H

//Thanks to StackOverflow :)
//Post: http://stackoverflow.com/questions/4484982/how-to-convert-typename-t-to-string-in-c
//Answer: http://stackoverflow.com/a/4485051/3554987
//Useful comment: http://stackoverflow.com/questions/4484982/how-to-convert-typename-t-to-string-in-c#comment4905627_4485051


// default implementation
template <typename T>
struct TypeName
{
    static const char* Get()
    {
        return typeid(T).name();
    }
};

// a specialization for each type of those you want to support
// and don't like the string returned by typeid
#define ENABLE_TYPENAME(A) template<> struct TypeName<A> { static const char *Get() { return #A; }};

#endif // TYPENAME_H
