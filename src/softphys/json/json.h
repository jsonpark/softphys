#ifndef SOFTPHYS_DATA_JSON_H_
#define SOFTPHYS_DATA_JSON_H_

#include <cstdint>
#include <string>
#include <map>
#include <vector>
#include <stdexcept>
#include <fstream>

#include "softphys/data/eigen.h"

namespace softphys
{
class Json
{
private:
  using IntType = std::int64_t;
  using UintType = std::uint64_t;
  using ObjectType = std::map<std::string, Json*>;
  using ArrayType = std::vector<Json*>;

  enum class Type
  {
    Object,
    Array,
    String,
    Int,
    Uint,
    Float,
    Boolean,
    Null,
  };

public:
  // Constructors
  Json() noexcept
    : type_(Type::Null)
  {
    value_.object_ptr_ = nullptr;
  }

  Json(const std::string& value)
    : type_(Type::String)
  {
    value_.string_ptr_ = new std::string(value);
  }

  Json(std::string&& value)
    : type_(Type::String)
  {
    value_.string_ptr_ = new std::string(std::move(value));
  }

  Json(IntType value) noexcept
    : type_(Type::Int)
  {
    value_.signed_integer_value_ = value;
  }

  Json(UintType value) noexcept
    : type_(Type::Uint)
  {
    value_.unsigned_integer_value_ = value;
  }

  Json(double value) noexcept
    : type_(Type::Float)
  {
    value_.double_value_ = value;
  }

  Json(bool value) noexcept
    : type_(Type::Boolean)
  {
    value_.boolean_value_ = value;
  }

  // Destructor
  ~Json()
  {
    Reset();
  }

  // Copy constructor
  Json(const Json& rhs)
    : type_(rhs.type_)
  {
    switch (rhs.type_)
    {
    case Type::Object:
      value_.object_ptr_ = new ObjectType();
      for (const auto& p : *rhs.value_.object_ptr_)
        value_.object_ptr_->insert(std::make_pair(p.first, new Json(p.second)));
      break;

    case Type::Array:
      value_.array_ptr_ = new ArrayType();
      for (const auto& p : *rhs.value_.array_ptr_)
        value_.array_ptr_->push_back(new Json(*p));
      break;

    case Type::String:
      value_.string_ptr_ = new std::string(*rhs.value_.string_ptr_);
      break;

    default:
      value_ = rhs.value_;
    }
  }

  // Copy assignment: copy-and-swap
  Json& operator = (Json rhs)
  {
    std::swap(type_, rhs.type_);
    std::swap(value_, rhs.value_);

    return *this;
  }

  // Move constructor
  Json(Json&& rhs) noexcept
    : type_(std::move(rhs.type_)), value_(std::move(rhs.value_))
  {
    rhs.type_ = Type::Null;
    value_.object_ptr_ = nullptr;
  }
  
  // Type
  bool IsObject()
  {
    return type_ == Type::Object;
  }

  bool IsArray()
  {
    return type_ == Type::Array;
  }

  bool IsString()
  {
    return type_ == Type::String;
  }

  bool IsInteger()
  {
    return IsSignedInteger() || IsUnsignedInteger();
  }

  bool IsSignedInteger()
  {
    return type_ == Type::Int;
  }

  bool IsUnsignedInteger()
  {
    return type_ == Type::Uint;
  }

  bool IsFloat()
  {
    return type_ == Type::Float;
  }

  bool IsBoolean()
  {
    return type_ == Type::Boolean;
  }

  bool IsNull()
  {
    return type_ == Type::Null;
  }

  // Getter
  template<typename T, std::enable_if_t<!std::is_integral_v<T> || std::is_same_v<T, bool>, int> = 0>
  T Get() const;

  template<>
  double Get<double>() const
  {
    switch (type_)
    {
    case Type::Float:
      return static_cast<double>(value_.double_value_);

    case Type::Int:
      return static_cast<double>(value_.signed_integer_value_);

    case Type::Uint:
      return static_cast<double>(value_.unsigned_integer_value_);

    default:
      return 0.;
    }
  }

  template<>
  float Get<float>() const
  {
    switch (type_)
    {
    case Type::Float:
      return static_cast<float>(value_.double_value_);

    case Type::Int:
      return static_cast<float>(value_.signed_integer_value_);

    case Type::Uint:
      return static_cast<float>(value_.unsigned_integer_value_);

    default:
      return 0.f;
    }
  }

  template<>
  bool Get<bool>() const
  {
    switch (type_)
    {
    case Type::Float:
      return value_.double_value_ != 0.;

    case Type::Int:
      return value_.signed_integer_value_ != 0;

    case Type::Uint:
      return value_.unsigned_integer_value_ != 0;

    default:
      return false;
    }
  }

  template<>
  std::string Get<std::string>() const
  {
    switch (type_)
    {
    case Type::String:
      return *value_.string_ptr_;

    default:
      return "";
    }
  }

  template<typename T, std::enable_if_t<std::is_signed_v<T>&& std::is_integral_v<T>, int> = 0>
  T Get() const
  {
    switch (type_)
    {
    case Type::Int:
      return static_cast<T>(value_.signed_integer_value_);

    case Type::Uint:
      return static_cast<T>(value_.unsigned_integer_value_);

    default:
      return T(0);
    }
  }

  template<typename T, std::enable_if_t<std::is_unsigned_v<T>&& std::is_integral_v<T>, int> = 0>
  T Get() const
  {
    switch (type_)
    {
    case Type::Int:
      return static_cast<T>(value_.signed_integer_value_);

    case Type::Uint:
      return static_cast<T>(value_.unsigned_integer_value_);

    default:
      return T(0);
    }
  }

  // Json with eigen
  template<>
  Vector3f Get<Vector3f>() const
  {
    if (type_ != Type::Array || Size() != 3)
      return Vector3f::Zero();

    Vector3f v;
    v(0) = (*this)[0].Get<float>();
    v(1) = (*this)[1].Get<float>();
    v(2) = (*this)[2].Get<float>();
    return v;
  }

  template<>
  Vector3d Get<Vector3d>() const
  {
    if (type_ != Type::Array || Size() != 3)
      return Vector3d::Zero();

    Vector3d v;
    v(0) = (*this)[0].Get<double>();
    v(1) = (*this)[1].Get<double>();
    v(2) = (*this)[2].Get<double>();
    return v;
  }

  template<>
  Quaterniond Get<Quaterniond>() const
  {
    if (type_ != Type::Array || Size() != 4)
      return Quaterniond::Identity();

    Quaterniond v;
    v.w() = (*this)[0].Get<double>();
    v.x() = (*this)[1].Get<double>();
    v.y() = (*this)[2].Get<double>();
    v.z() = (*this)[3].Get<double>();
    return v;
  }

  // Object
  const Json& At(const std::string& key) const
  {
    if (type_ == Type::Object)
      return *value_.object_ptr_->at(key);

    throw std::runtime_error("Json exception: type should be object when using [] operator with key");
  }

  Json& At(const std::string& key)
  {
    return const_cast<Json&>(static_cast<const Json&>(*this).At(key));
  }

  bool HasKey(const std::string& key) const
  {
    if (type_ == Type::Object)
      return value_.object_ptr_->find(key) != value_.object_ptr_->cend();

    throw std::runtime_error("Json exception: type should be object when calling HasKey() function");
  }

  Json& operator [] (const std::string& key)
  {
    if (type_ == Type::Null)
      type_ = Type::Object;

    if (type_ == Type::Object)
      return *value_.object_ptr_->operator[](key);

    throw std::runtime_error("Json exception: type should be object when using [] operator with key");
  }

  Json& operator [] (std::string&& key)
  {
    if (type_ == Type::Null)
      type_ = Type::Object;

    if (type_ == Type::Object)
      return *value_.object_ptr_->operator[](std::move(key));

    throw std::runtime_error("Json exception: type should be object when using [] operator with key");
  }

  // Array
  const Json& operator [] (int idx) const
  {
    if (type_ == Type::Array)
      return *value_.array_ptr_->at(idx);

    throw std::runtime_error("Json exception: type should be array when using [] operator with integer index");
  }

  Json& operator [] (int idx)
  {
    return const_cast<Json&>(static_cast<const Json&>(*this).operator[](idx));
  }

  // Container
  int Size() const
  {
    if (type_ == Type::Array)
      return value_.array_ptr_->size();

    else if (type_ == Type::Object)
      return value_.object_ptr_->size();

    throw std::runtime_error("Json exception: Size() should be called on an array or an object");
  }

  // Reset
  void Reset()
  {
    switch (type_)
    {
    case Type::Object:
      for (const auto& p : *value_.object_ptr_)
        delete p.second;
      delete value_.object_ptr_;
      break;

    case Type::Array:
      for (auto p : *value_.array_ptr_)
        delete p;
      delete value_.array_ptr_;
      break;

    case Type::String:
      delete value_.string_ptr_;
      break;
    }

    type_ = Type::Null;
  }

  // istream
  friend std::istream& operator >> (std::istream& in, Json& j)
  {
    j.Reset();

    // TODO: reset before throw (ex. created object will never be deleted when it throws while parsing object)

    // json = element
    // element = ws value ws
    // value = object | array | string | number | "true" | "false" | "null"

    char c[16];
    while (true)
    {
      in.read(c, 1);

      if (IsWhitespace(c[0]))
        continue;

      if (c[0] == '{') // object
      {
        j.type_ = Type::Object;
        j.value_.object_ptr_ = new ObjectType;

        // object = '{' ws '}' | '{' members '}'
        // members = member | member ',' members
        // member = ws string ws ':' element
        while (true)
        {
          in.read(c, 1);
          if (IsWhitespace(c[0]))
            continue;
          if (c[0] == '}')
            break;
          if (c[0] == '\"')
          {
            std::string key = ParseStringAfterQuotation(in);

            bool closed = false;
            while (true)
            {
              in.read(c, 1);
              if (IsWhitespace(c[0]))
                continue;
              else if (c[0] == ':')
              {
                j.value_.object_ptr_->insert(std::make_pair(key, new Json));
                in >> *(j.value_.object_ptr_->at(key));
                break;
              }
              else
                throw std::exception("Json parse error: \':\' required after a key as a string while parsing an object");
            }

            while (true)
            {
              in.read(c, 1);
              if (IsWhitespace(c[0]))
                continue;
              else if (c[0] == ',')
                break;
              else if (c[0] == '}')
              {
                closed = true;
                break;
              }
              else
                throw std::exception("Json parse error: while parsing an object");
            }

            if (closed)
              break;
          }
        }

        break;
      }
      else if (c[0] == '[') // array
      {
        j.type_ = Type::Array;
        j.value_.array_ptr_ = new ArrayType;

        // array = '[' ws ']' | '[' elements ']'
        // elements = element | element ',' elements
        while (true)
        {
          in.read(c, 1);
          if (IsWhitespace(c[0]))
            continue;
          if (c[0] == ']')
            break;

          in.seekg(-1, std::ios_base::cur);

          auto element = new Json;
          in >> *element;
          j.value_.array_ptr_->push_back(element);

          bool closed = false;
          while (true)
          {
            in.read(c, 1);
            if (IsWhitespace(c[0]))
              continue;
            else if (c[0] == ',')
              break;
            else if (c[0] == ']')
            {
              closed = true;
              break;
            }
            else
              throw std::exception("Json parse error: should come \',\' or \']\' while parsing an array");
          }

          if (closed)
            break;
        }

        break;
      }
      else if (c[0] == '"') // string
      {
        j.type_ = Type::String;
        j.value_.string_ptr_ = new std::string(ParseStringAfterQuotation(in));
        break;
      }
      else if (c[0] == 't') // true
      {
        in.read(c, 3);
        if (std::strncmp(c, "rue", 3) == 0)
        {
          j.type_ = Type::Boolean;
          j.value_.boolean_value_ = true;
        }
        else
          throw std::exception("Json parse error: \"true\"");

        break;
      }
      else if (c[0] == 'f') // false
      {
        in.read(c, 4);
        if (std::strncmp(c, "alse", 4) == 0)
        {
          j.type_ = Type::Boolean;
          j.value_.boolean_value_ = false;
        }
        else
          throw std::exception("Json parse error: \"false\"");

        break;
      }
      else if (c[0] == 'n') // null
      {
        in.read(c, 3);
        if (std::strncmp(c, "ull", 3) == 0)
          j.type_ = Type::Null;
        else
          throw std::exception("Json parse error: \"null\"");

        break;
      }
      else // number
      {
        double sign = 1.;
        if (c[0] == '-')
          sign = -1.;
        else
          in.seekg(-1, std::ios_base::cur);

        // int frac exp
        bool frac = false;
        bool exp = false;

        IntType integer_part = 0;
        double frac_part = 0.;
        int exp_part = 0;

        in.read(c, 1);
        if (c[0] == '0') // '0'
        {
          in.read(c, 1);
          if (c[0] == '.') // frac
            frac = true;
          else if (c[0] == 'e' || c[0] == 'E') // exp
            exp = true;
          else
          {
            in.seekg(-1, std::ios_base::cur);
            break;
          }
        }
        else if (IsDigit(c[0])) // onenine digits
        {
          integer_part = c[0] - '0';
          while (true)
          {
            in.read(c, 1);
            if (IsDigit(c[0]))
              integer_part = integer_part * 10 + c[0] - '0';
            else if (c[0] == '.') // frac
            {
              frac = true;
              break;
            }
            else if (c[0] == 'e' || c[0] == 'E') // exp
            {
              exp = true;
              break;
            }
            else
            {
              in.seekg(-1, std::ios_base::cur);
              break;
            }
          }
        }
        else
          throw std::exception("Json parse error: digit expected while parsing number");

        if (frac)
        {
          in.read(c, 1);
          if (!IsDigit(c[0]))
            throw std::exception("Json parse error: digit expected for fractional part while parsing number");
          frac_part = (c[0] - '0') * 0.1;

          double frac_digit = 0.01;
          while (true)
          {
            in.read(c, 1);
            if (IsDigit(c[0]))
            {
              frac_part += (c[0] - '0') * frac_digit;
              frac_digit /= 10.;
            }
            else if (c[0] == 'e' || c[0] == 'E') // exp
            {
              exp = true;
              break;
            }
            else
            {
              in.seekg(-1, std::ios_base::cur);
              break;
            }
          }
        }

        if (exp)
        {
          int exp_sign = 1;
          in.read(c, 1);
          if (c[0] == '+');
          else if (c[0] == '-')
            exp_sign = -1;
          else if (IsDigit(c[0]))
            in.seekg(-1, std::ios_base::cur);
          else
            throw std::exception("Json parse error: digit expected in exponential part while parsing a number");

          while (true)
          {
            in.read(c, 1);
            if (IsDigit(c[0]))
              exp_part = exp_part * 10 + c[0] - '0';
            else
            {
              in.seekg(-1, std::ios_base::cur);
              break;
            }
          }

          exp_part *= exp_sign;
        }

        if (frac || exp)
        {
          j.type_ = Type::Float;
          j.value_.double_value_ = (static_cast<double>(integer_part) + frac_part) * sign;
          for (int i = 0; i < exp_part; i++)
            j.value_.double_value_ *= 10.;
          for (int i = 0; i < (-exp_part); i++)
            j.value_.double_value_ /= 10.;
        }
        else
        {
          j.type_ = Type::Int;
          j.value_.signed_integer_value_ = integer_part * static_cast<int>(sign);
        }

        break;
      }
    }

    return in;
  }

private:
  union
  {
    double double_value_;
    bool boolean_value_;
    IntType signed_integer_value_;
    UintType unsigned_integer_value_;
    std::string* string_ptr_;
    ObjectType* object_ptr_;
    ArrayType* array_ptr_;
  } value_;

  Type type_ = Type::Null;

private:
  static bool IsWhitespace(char c)
  {
    return c == 9 || c == 0xA || c == 0xD || c == 0x20;
  }

  static bool IsHex(char c)
  {
    return '0' <= c && c <= '9' || 'A' <= c && c <= 'F' || 'a' <= c && c <= 'f';
  }

  static bool IsDigit(char c)
  {
    return '0' <= c && c <= '9';
  }

  static std::string ParseStringAfterQuotation(std::istream& in)
  {
    std::string str;
    char c[16];
    while (true)
    {
      in.read(c, 1);
      if (c[0] == '\"')
        break;
      else if (c[0] == '\\')
      {
        in.read(c + 1, 1);
        if (c[0] == 'u') // unicode
        {
          in.read(c + 2, 4);

          // Checking hexcode
          for (int i = 2; i < 6; i++)
            if (!IsHex(c[i]))
              throw std::exception("Json parse error: hexdecimal digit \\uXXXX in string");

          c[6] = 0;
          str += c;
        }
        else if (c[1] == '\"')
          str += '\"';
        else if (c[1] == '\\')
          str += '\\';
        else if (c[1] == '/')
          str += '/';
        else if (c[1] == 'b')
          str += '\b';
        else if (c[1] == 'f')
          str += '\f';
        else if (c[1] == 'n')
          str += '\n';
        else if (c[1] == 'r')
          str += '\r';
        else if (c[1] == 't')
          str += '\t';
        else
          throw std::exception("Json parse error: wrong escape");
      }
      else
        str += c[0];
    }

    return str;
  }
};
}

#endif // SOFTPHYS_DATA_JSON_H_
