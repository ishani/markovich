// generated by markovich:tablegen
// ishani.org 2021

#include "inline/common-all-begin.inl"

#include "mk-selector-slavic.inl"
#include "mk-roots-slavic.inl"
#include "mk-selector-england.inl"
#include "mk-roots-england.inl"
#include "mk-selector-scotland.inl"
#include "mk-roots-scotland.inl"
#include "mk-selector-wales.inl"
#include "mk-roots-wales.inl"
#include "mk-selector-japan.inl"
#include "mk-roots-japan.inl"
#include "mk-selector-latin.inl"
#include "mk-roots-latin.inl"
#include "mk-selector-arabic.inl"
#include "mk-roots-arabic.inl"
#include "mk-selector-thailand.inl"
#include "mk-roots-thailand.inl"

#define MKV_CHOICE_LIST( _call )  \
    _call( slavic )  \
    _call( england )  \
    _call( scotland )  \
    _call( wales )  \
    _call( japan )  \
    _call( latin )  \
    _call( arabic )  \
    _call( thailand )  

namespace mk {

enum class Choice {
    slavic,
    england,
    scotland,
    wales,
    japan,
    latin,
    arabic,
    thailand,
};

} // namespace mk

#include "inline/common-all-end.inl"
