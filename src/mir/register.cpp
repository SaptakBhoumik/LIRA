#include "mir/register.hpp"

namespace LIRA {
namespace MIR{
LocalRegister::LocalRegister(std::string dest_register_name, IR::TypeExprPtr type,bool artificial, bool synthetic, bool nonnull, bool nopoison, 
                                     bool nnan, bool ninf, bool noalias, std::string original_name, std::string scope, std::size_t dereferenceable_bytes, 
                                     std::size_t alignment){
    this->dest_register_name = dest_register_name;
    this->type = type;

    this->artificial = artificial;
    this->synthetic = synthetic;
    this->nonnull = nonnull;
    this->nopoison = nopoison;
    this->nnan = nnan;
    this->ninf = ninf;
    this->noalias = noalias;

    this->original_name = original_name;
    this->scope = scope;
    this->dereferenceable_bytes = dereferenceable_bytes;
    this->alignment = alignment;    
}

void LocalRegister::set_alignment(std::size_t alignment){
    this->alignment = alignment;
}

std::string LocalRegister::get_dest_register_name() const{
    return dest_register_name;
}
IR::TypeExprPtr LocalRegister::get_type() const{
    return type;
}

bool LocalRegister::is_artificial() const{
    return artificial;
}
bool LocalRegister::is_synthetic() const{
    return synthetic;
}
bool LocalRegister::is_nonnull() const{
    return nonnull;
}
bool LocalRegister::is_nopoison() const{
    return nopoison;
}
bool LocalRegister::is_nnan() const{
    return nnan;
}
bool LocalRegister::is_ninf() const{
    return ninf;
}
bool LocalRegister::is_noalias() const{
    return noalias;
}

std::string LocalRegister::get_original_name() const{
    return original_name;
}
std::string LocalRegister::get_scope() const{
    return scope;
}
std::size_t LocalRegister::get_dereferenceable_bytes() const{
    return dereferenceable_bytes;
}
std::size_t LocalRegister::get_alignment() const{
    return alignment;
}

std::string LocalRegister::to_string() const{
    std::string result = type->to_string() + ":" + dest_register_name;
    if(artificial){
        result += " #[artificial]";
    }
    if(synthetic){
        result += " #[synthetic]";
    }
    if(nonnull){
        result += " #[nonnull]";
    }
    if(nopoison){
        result += " #[nopoison]";
    }
    if(nnan){
        result += " #[nnan]";
    }
    if(ninf){
        result += " #[ninf]";
    }
    if(noalias){
        result += " #[noalias]";
    }

    if(!original_name.empty()){
        result += " #[name(str:" + original_name + ")]";
    }
    if(!scope.empty()){
        result += " #[set_scope(scope:" + scope + ")]";
    }
    if(dereferenceable_bytes > 0){
        result += " #[dereferenceable_bytes(i64:" + std::to_string(dereferenceable_bytes) + ")]";
    }
    if(alignment > 0){
        result += " #[alignment(i64:" + std::to_string(alignment) + ")]";
    }
    return result;
}
}
}