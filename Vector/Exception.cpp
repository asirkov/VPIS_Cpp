#include <string>

class Exception {
protected:
    std::string message;
    std::string defaultMessage = "An exception occured. ";
public:
    Exception() : message(defaultMessage) {};
    Exception(std::string msg) {
        message = defaultMessage + "Message: " + msg;
    };
    Exception(std::string msg, std::string method) {
        //Exception(msg);
        //message += "at method \"" + method + "\".";
        message = defaultMessage + "Message: " + msg + " at method \"" + method + "\".";
    };

    std::string getMessage() { return message; };

    virtual ~Exception() {}
};

class IndexOutOfBoundsException : public Exception {
public:
    IndexOutOfBoundsException() : Exception("Index out of bound! ") {}
    IndexOutOfBoundsException(std::string method ) : Exception("Index out of bound! ", method) {}
    virtual ~IndexOutOfBoundsException() {}
};

class NotEqualsSizesException : public Exception {
public:
    //NotEqualsSizesException(std::string msg = "Sizes is not equals!") { setMessage(msg); }
    NotEqualsSizesException() : Exception("Sizes is not equals! ") {}
    NotEqualsSizesException(std::string method ) : Exception("Sizes is not equals! ", method) {}
    virtual ~NotEqualsSizesException() {}
};
