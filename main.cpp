#include <iostream>

//#define DEBUG_LOG

using namespace std;

class String
{

private:
    char *str;
    int size;

    void create(int size)
    {
        this->size = size;
        str = new char[size];
    }

    void copy(const String &source)
    {
        #ifdef DEBUG_LOG
            cout << "Call copy constructor" << endl;
        #endif
        create(source.size);
        for(int i = 0; i < size; i++)
        {
            str[i] = source.str[i];
        }
    }

    void clear()
    {
        delete[] str;
        create(1);
    }

    void clear(int size)
    {
        delete[] str;
        create(size);
    }

public:
    String()
    {
        create(1);
    }

    String(char c)
    {
        create(2);
        str[0] = c;
    }

    String(const std::string s)
    {
        create(s.size());
        for(int i = 0; i < size; i++) {str[i] = s[i];};
    }

    int length()
    {
        return size;
    }

    String(const String &source)
    {
        copy(source);
    }

    ~String()
    {
        #ifdef DEBUG_LOG
            cout << "Call destructor" << endl;
        #endif
        delete[] str;
    }

    String(String &&str_to_move)
    {
        #ifdef DEBUG_LOG
            cout << "Call move constructor" << endl;
        #endif
        str = str_to_move.str;
        size = str_to_move.size;
        str_to_move.str = nullptr;
        str_to_move.size = 0;
    }

    String reverse()
    {
        String s1(*this);
        int i = 0;
        int j = s1.size -1;
        while (i < j)
        {
            char temp = s1.str[i];
            s1.str[i] = s1.str[j];
            s1.str[j] = temp;
            i++;
            j--;
        }
        return s1;
    }

    bool insert(String substr, int pos)
    {
        if ((pos > size)||(pos < 0)){return false;}
        String source(*this);
        String sbstr(substr);
        delete[] str;
        create(size + sbstr.size);
        int i = 0;
        for(; i < pos; i++)
        {
            str[i] = source.str[i];
        }
        for(; i < pos + sbstr.size; i++)
        {
            str[i] = sbstr.str[i - pos];
        }
        for(; i < size; i++)
        {
            str[i] = source.str[i-sbstr.size];
        }
        return true;
    }

    bool insert(char substr, int pos)
    {
        return (this->insert(String(substr), pos));
    }

    bool insert(std::string substr, int pos)
    {
        return (this->insert(String(substr), pos));
    }


    void append(String substr)
    {
        this->insert(substr, size);
    }

    void append(char substr)
    {
        this->insert(String(substr), size);
    }

    void append(std::string substr)
    {
        this->insert(substr, size);
    }

    bool remove(int pos, int length)
    {
        if (pos < 0) return false;
        if (((length + pos) > size)||(length == 0)){length = size - pos;}
        String source(*this);
        delete[] str;
        create(size - length);
        int i = 0;
        for(; i < pos; i++)
        {
            str[i] = source.str[i];
        }
        for(; i < size; i++)
        {
            str[i] = source.str[i + length];
        }
        return true;
    }

    int contains(String substr)
    {
        int pos =-1;
        if (size < substr.size) return -1;
        for (int i = 0; i < size; i++)
        {
             if ((str[i] == substr.str[0])&&((size - i)>=substr.size))
             {
                 for (int j = 0; j < substr.size; j++)
                 {
                     if (str[i + j] != substr.str[j]) {pos = -1; break;}
                     pos = i;
                 }
                 if (pos != -1) {break;}
             }
        }
        return pos;
    }

    int contains(const std::string s)
    {
        return this->contains((String)s);
    }

    std::string toStdString()
    {
        std::string s="";
        for (int i = 0;i < size; i++)
        {
            s += str[i];
        }
        return s;
    }

    void show(std::string message="")
    {
        if (str == nullptr)
        {
            cout << "Null" << endl;
            return;
        }
        if (message == "") {message = "Content of the custom String class: ";}
        cout << message ;
        for (int i = 0; i < size; i++)
        {
            cout << str[i];
        }
        cout << endl;
    }

    String&  operator=(const String& source)
    {
        #ifdef DEBUG_LOG
            cout << "Call operator '=' with String" << endl;
        #endif
        if (this != &source)
        {
            delete[] str;
            copy(source);
        }
        return *this;
    }

    String&  operator=(const std::string& right)
    {
        #ifdef DEBUG_LOG
            cout << "Call operator '=' with std::string" << endl;
        #endif
        String source(right);
        if (this != &source)
        {
            delete[] str;
            copy(source);
        }
        return *this;
    }

    String&  operator+=(const String& right)
    {
        #ifdef DEBUG_LOG
            cout << "Call operator '+=' with String" << endl;
        #endif
        this->append(right);
        return *this;
    }

    String&  operator+=(const std::string& right)
    {
        #ifdef DEBUG_LOG
            cout << "Call operator '+=' with std::string" << endl;
        #endif
        this->append(right);
        return *this;
    }

    String&  operator=(String&& str_to_move)
    {
        #ifdef DEBUG_LOG
            cout << "Call move costructor via operator=" << endl;
        #endif
        str = str_to_move.str;
        size = str_to_move.size;
        str_to_move.str = nullptr;
        str_to_move.size = 0;
        return *this;
    }


    friend std::ostream& operator<<(std::ostream& out, const String& source);
    friend std::istream& operator>>(std::istream& in, String& source);
    friend const String operator+(const String& lhs, const String& rhs);
    friend const String operator+(const std::string& lhs, const String& rhs);
    friend const String operator+(const String& lhs, const std::string& rhs);

    bool  operator==(const String& right)
    {
        #ifdef DEBUG_LOG
            cout << "Call operator '==' with String" << endl;
        #endif
        if ((right.size == size)&&((this->contains(right)) != -1)) {return true;}
        return false;
    }

    bool  operator==(const std::string& right)
    {
        #ifdef DEBUG_LOG
            cout << "Call operator '==' with std::string" << endl;
        #endif
        String source(right);
        if ((source.size == size)&&((this->contains(right)) != -1)) {return true;}
        return false;
    }

    operator std::string() { return str; }

};

std::ostream& operator<<(std::ostream& out, const String& source)
{
    out << "String contains = ";
    for(int i  = 0; i < source.size; ++i)
    {
      out << source.str[i];
    }
    return  out << std::endl;
}

std::istream& operator>>(std::istream& in, String& source)
{
    std::string s;
    in >> s;
    source.clear(s.length());
    for(auto i  = 0; i < source.size; ++i)
    {
        source.str[i] = s[i];
    }
    return in;
}


const String operator+(const String& lhs, const String& rhs)
{
    String stril(lhs);
    stril.append(rhs);
    return stril;
}

const String operator+(const std::string& lhs, const String& rhs)
{
    String stril(lhs);
    stril.append(rhs);
    return stril;
}

const String operator+(const String& lhs, const std::string& rhs)
{
    String stril(lhs);
    stril.append(rhs);
    return stril;
}

int main()
{
    cout << "=============================================" << endl;
    cout << "Show work of custom class String" << endl;
    cout << "=============================================" << endl;
    cout << "Object 'a' creation and initialization with string literal" << endl;
    String a("This is object 'a'");
    a.show("Content of object 'a': ");
    cout << "---------------------------------------------" << endl;

    cout << "=============================================" << endl;
    cout << "Object 'b' creation and initialization with reverse of object 'a'" << endl;
    cout << "=============================================" << endl;
    String b = a.reverse();
    b.show("Content of object 'b': ");
    cout << "b.length() = " << b.length() << endl;
    cout << "---------------------------------------------" << endl;

    cout << "=============================================" << endl;
    cout << "Object 'c' creation as copy of object 'a'" << endl;
    cout << "=============================================" << endl;
    String c(a);
    c.show("Content of object 'c': ");
    cout << "---------------------------------------------" << endl;

    cout << "=============================================" << endl;
    cout << "Do 'c = b'" << endl;
    cout << "=============================================" << endl;
    c = b;
    cout << "Show 'c'" << endl;
    c.show("Content of object 'c': ");
    cout << "---------------------------------------------" << endl;

    cout << "=============================================" << endl;
    cout << "Do 'a += b'" << endl;
    cout << "=============================================" << endl;
    a += b;
    cout << "Show 'a'" << endl;
    a.show("Content of object 'a': ");
    cout << "---------------------------------------------" << endl;

    cout << "=============================================" << endl;
    cout << "Show move constructor and operator" << endl;
    cout << "=============================================" << endl;
    String d = (String("For move"));
    d.show("Content of object 'd': ");

    cout << "Create object 'f'" << endl;
    String f;
    f.show("Content of object 'f': ");
    cout << "Use move operator=" << endl;
    f = String("We did it");
    f.show("Content of object 'f': ");
    cout << "---------------------------------------------" << endl;

    cout << "=============================================" << endl;
    cout << "Set 'c'" << endl;
    cout << "=============================================" << endl;
    c.show("Content of object 'c' before: ");
    c = "zsd";
    c.show("Content of object 'c' after: ");
    cout << "---------------------------------------------" << endl;

    cout << "=============================================" << endl;
    cout << "String concatenation using operator+" << endl;
    cout << "=============================================" << endl;
    c = "1st part";
    b = "2d part";
    a.show("Content of object 'a': ");
    c.show("Content of object 'c': ");
    b.show("Content of object 'b': ");
    cout << "Concatenation: 'a = c + ' ' + b': " << endl;
    a = c + " " + b;
    a.show("Content of object 'a': ");
    c.show("Content of object 'c': ");
    cout << "---------------------------------------------" << endl;

    cout << "=============================================" << endl;
    cout << "Show String append() function" << endl;
    cout << "=============================================" << endl;
    a = "Source";
    a.show("Content of object 'a': ");
    cout << "Call a.append('string') " << endl;
    a.append(" string");
    a.show("Content of object 'a': ");
    cout << "---------------------------------------------" << endl;

    cout << "=============================================" << endl;
    cout << "Show String insert() function" << endl;
    cout << "=============================================" << endl;
    cout << "Call a.insert('modified ', 7) " << endl;
    a.insert("1st modified ", 7);
    a.show("Content of object 'a': ");
    cout << "---------------------------------------------" << endl;

    cout << "=============================================" << endl;
    cout << "Show String remove() function" << endl;
    cout << "=============================================" << endl;
    cout << "Call a.remove(7, 4) " << endl;
    a.remove(7, 4);
    a.show("Content of object 'a': ");
    cout << "---------------------------------------------" << endl;

    cout << "=============================================" << endl;
    cout << "Show String contains() function" << endl;
    cout << "=============================================" << endl;
    cout << "Call a.contains('trash') " << endl;
    int pos = a.contains("trash");
    cout << "Receive -1 which means the substring 'trash' was not found : " << pos << endl;

    cout << "Call a.contains('string') " << endl;
    pos = a.contains("string");
    cout << "Receive pos : " << pos << endl;
    cout << "---------------------------------------------" << endl;

    cout << "=============================================" << endl;
    cout << "Show String == operator " << endl;
    cout << "=============================================" << endl;
    cout << "Show String == operator (bool equal = (a==a);)" << endl;
    bool equal = (a==a);
    cout << "Receive equal : " << (equal? "true":"false") << endl;

    cout << "Show String == operator (bool equal = (a==b);)" << endl;
    b = "trash";
    equal = (a==b);
    cout << "Receive equal : " << (equal? "true":"false") << endl;

    cout << "Show String == operator (bool equal = (a=='bla-bla');)" << endl;
    equal = (a=="bla-bla");
    cout << "Receive equal : " << (equal? "true":"false") << endl;

    //c = "Source modified string";
    cout << "Show String == operator (bool equal = (a=='Source modified string');)" << endl;
    equal = (a=="Source modified string");
    cout << "Receive equal : " << (equal? "true":"false") << endl;

    cout << "Show String == operator (bool equal = (a==c);)" << endl;
    c = "Source modified string";
    equal = (a==c);
    cout << "Receive equal : " << (equal? "true":"false") << endl;
    cout << "---------------------------------------------" << endl;

    cout << "=============================================" << endl;
    cout << "Show operator + " << endl;
    cout << "=============================================" << endl;
    a = "String a";
    c = "String c";
    a.show("Content of object 'a': ");
    c.show("Content of object 'c': ");

    cout << "Show c + ' some add to '" << endl;
    a = c + " some add to ";
    a.show("Content of object 'a': ");

    cout << "Show ' some add to ' + c" << endl;
    a = " some add to " + c;
    a.show("Content of object 'a': ");
    cout << "---------------------------------------------" << endl;

    cout << "=============================================" << endl;
    cout << "Show operator << " << endl;
    cout << "=============================================" << endl;
    cout << a << endl;
    cout << "---------------------------------------------" << endl;

    cout << "=============================================" << endl;
    cout << "Show operator >> and cast to (std::string)" << endl;
    cout << "=============================================" << endl;
    cout << "Type your message :";
    cin >> a ;

    std::string cast;

    cast = (std::string)a;
    cout << "You type '" << cast << "'" << endl;
    cout << "---------------------------------------------" << endl;

    return 0;
}
