# Reflect

Reflection is the ability for a computer program to examine, introspect, and modify its own structure and behavior at runtime. 

Reflect is a C++14, header-only library used to provide basic reflection and introspection to classes. It is designed to be used in conjunction with serialization libraries (such as [JsonCpp][jsoncpp]) to provide simple and quick conversion to and from external serialized formats. 

[jsoncpp]: https://github.com/open-source-parsers/jsoncpp


## Documentation

Reflect documentation is generated using [Doxygen][doxygen]

[doxygen]: http://www.doxygen.org


## Using Reflect in your project

As Reflect is a solely header-only library, you do not need to include any additional libraries. The include path within the Reflect folder should be added to your compiler include path. Relfect headers should be included as follows: 

```C++
#include <reflect/reflect.hpp>
```

Below is a simple example of exposing a class with getters and setters to the meta engine:

```C++
#include <string>

class Account
{
private:
    int         m_age;
    std::string m_name;

public:
    explicit Account() : m_age(0), m_name() {}
    ~Account() = default;

    int getAge() const { return m_age; }
    void setAge(int age) { m_age = age; }

    const std::string& getName() const { return m_name; }
    void setName(const std::string& name) { m_name = name; }
};

// Include reflect here to expose the class to the meta engine!
#include <reflect/reflect.hpp>

// The exposed class must be contained within the reflect namespace.
namespace reflect
{
    // This function definition is important, it must match the example
    // other it may not be properly registered with the meta engine!
    template <>
    inline auto register_class<Account>()
    {
        // Each property needs a mapped name, and a function pointer to a 
        // getter and optional setter.
        return properties(
            property("age", &Account::getAge, &Account::setAge),
            property("name", &Account::getName, &Account::setName)
        );
    }
}
```

Once the class has been exposed, you can create meta_class object and alter the values of a class by using the unique names, for example:

```C++
Account account;
// Set the default age to 10.
account.setAge(10);

// Create a meta object which will reference the object.
reflect::meta_class<Account> data(account);
// The meta-data can read or write to the registered member variables.
data.set_member<int>("age", 15); // Now 15!
```

If you want Reflect to directly reference member variables, rather than rely on getters and setters; use the following syntax:

```C++
class Account 
{
    friend auto reflect::register_class<Account>();
    //...
}
```

Member variables are added to property objects with the same syntax as mentioned before.

### Examples

Examples will (eventually) be provided in examples folder.

## Contributing to Reflect

Reflect is an open-source, free meta-data libary. Feel free to pull or contribute towards the project, or comment if you have any questions or suggestions for improvement.

### Building and testing with CMake

[CMake][] is a C++ Makefiles/Solution generator. It is usually available on most Linux system as a package. On Ubuntu:

```
sudo apt-get install cmake
```

[CMake]: http://www.cmake.org

When running CMake, a few parameters are required:

* A build directory where the makefiles/solution are generated. It is also used to store objects, libraries and executables files.
* The generator to use: makefiles or Visual Studio solution? What version or Visual Studio, 32 or 64 bits solution?

CMake is used within the project strictly for building and running the unit tests (which are created with [Catch][catch]) as Reflect does not include any source files.

[catch]: https://github.com/philsquared/Catch

No additional arguments are needed for CMake to build the project. Catch is added as a submodule and should automatically be pulled into the project.

To run the included unit tests; if you are using linux just run the command:

```
make test
```

If you are using Windows and Visual Studio, select the reflect_tests as the Startup project, and select to run the project without debugging.

## License

See the `LICENSE` file for details. In summary, Reflect is licensed under the MIT license, or public domain if desired and recognized in your jurisdiction.