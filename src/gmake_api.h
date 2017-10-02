#pragma once

#include <string>
#include <experimental/string_view>

#include <memory>

namespace gmake {

struct gmk_deleter {
  void operator()( char*& ptr );
};

class ExpressionBase {
private:
  std::unique_ptr<char, gmk_deleter> expr_;

  ExpressionBase() = delete;

  ExpressionBase( const ExpressionBase& ) = delete;
  ExpressionBase& operator=( const ExpressionBase& ) = delete;

protected:
  ExpressionBase( char* );

  ExpressionBase( const ExpressionBase&& );
  ExpressionBase& operator=( const ExpressionBase&& );

  ~ExpressionBase() {}

  char* get() const { return expr_.get(); }
public:
  char* release() { return expr_.release(); }
};

class Expression : public ExpressionBase {
private:
  typedef std::experimental::string_view string_view_t;

  Expression() = delete;

public:
  Expression( char* data )
  : ExpressionBase( data ) {}
  
  Expression( string_view_t sv );

  Expression( const Expression&& );
  Expression& operator=( const Expression&& );

  string_view_t string_view() const {
    return this->get();
  }

  Expression&& expand() const;
  Expression&& clone() const;
};

}
