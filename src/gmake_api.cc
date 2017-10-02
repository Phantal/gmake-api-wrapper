#include "gmake_api.h"

#include <string.h>
#include <string>
#include <utility>

#include <experimental/string_view>


extern "C" {
#include <gnumake.h>
}

namespace gmake {

void gmk_deleter::operator()( char*& ptr ) {
  gmk_free( ptr );
  ptr = NULL;
}

ExpressionBase::ExpressionBase( char* data )
  : expr_( data, gmk_deleter() ) {}

// Delegating constructor
Expression::Expression( string_view_t sv )
: Expression( strncpy( gmk_alloc( sv.length() ), sv.data(), sv.length() ) ) {}

Expression&& Expression::expand() const {
  return std::move( Expression( gmk_expand( this->get() ) ) );
}

Expression&& Expression::clone() const {
  return std::move( Expression( this->get() ) );
}

}
