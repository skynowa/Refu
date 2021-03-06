/**
** Copyright (c) 2011-2012, Karapetsas Eleftherios
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
**  1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
**  2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the distribution.
**  3. Neither the name of the Original Author of Refu nor the names of its contributors may be used to endorse or promote products derived from
**
**  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
**  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
**  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
**  SERVICES;LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
**  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
**  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**/

#ifndef RF_XMLTAG_H
#define RF_XMLTAG_H

#include <rf_options.h>
#ifdef RF_MODULE_DF_XML //XML module check

#include <stdarg.h>
//include the ReFu string
#include <rf_string.h>
#include <Data_Structures/rfc_list.h>// For RF_ListP
#include <rf_localmem.h>

#ifdef __cplusplus
extern "C"
{///opening bracket for calling from C++
#endif

/**
** @internal
** @date 10/04/2011
** @author Lefteris
** @endinternal
** @brief An XML Tag handle
**
** The XML tag represents
** an XML tag of an xml file. Contains
** all the data expected of an xml tag
**/
typedef struct RF_XMLTag
{
    //! The name of the tag
    RF_String name;
    //! The children tags of this tag
    RF_ListP   children;
    //! The attributes of this tag
    RF_ListP attributes;
    //! The value of the attributes of this tag
    RF_ListP    attribValues;
    //!The contents of the tag , basically anything inside the tag which is not another tag.
    RF_StringX contents;
    //! The parent tag
    struct RF_XMLTag*   parent;
}RF_XMLTag;


//! @memberof RF_XMLTag
//! @brief Creates a temporary XML Tag
//!
//! A macro to be used only inside a function call that accepts @ref an  RF_XMLTag to create a Temporary RF_XMLtag*
//! that will be used by the function. This macro accepts from 2 to 8 arguments
//!
//! @param parent A pointer to the parent tag of this tag
//! @param name Give the name of the tag as an @ref RF_String. @inhtype{String,StringX} @slitToStr
//! @param content \rfoptional{0} An optional string with the tag's contents. If omitted
//! or if zero is given then the tag will have no content. @inhtype{String,StringX} @slitToStr
//! @note if This parameter and the rest are omitted a more lightweight version of this function is called
//! @param attrN \rfoptional{0} The number of attributes this tag will have. The number you give here will basically
//! also be the number of additional arguments to follow. The additional arguments to follow should be @c attrN*2
//! an AttributeName and an AttributeValue for each attribute
//! @extraVarArgLim
//! @param ... Attribute names and values should follow as strings.
//! @inhtype{String,StringX} @slitToStr
//! @return The newly initialized XML tag
#if defined(RF_IAMHERE_FOR_DOXYGEN)
i_DECLIMEX_ RF_XMLTag* RFXML_(RF_XMLTag* parent,void* name,void* content,unsigned char attrN,...);
#else
#define RFXML_(...) rfXMLTag_CreateLocal(__VA_ARGS__)
#endif
//! @internal
//! @memberof RF_XMLTag
//! @brief Allocates and returns an XML Tag from local memory
//!
//! @param parent A pointer to the parent tag of this tag
//! @param name Give the name of the tag as an @ref RF_String. @inhtype{String,StringX} @slitToStr
//! @param content \rfoptional{0} An optional string with the tag's contents. If omitted
//! or if zero is given then the tag will have no content. @inhtype{String,StringX} @slitToStr
//! @note if This parameter and the rest are omitted a more lightweight version of this function is called
//! @param attrN \rfoptional{0} The number of attributes this tag will have. The number you give here will basically
//! also be the number of additional arguments to follow. The additional arguments to follow should be @c attrN*2
//! an AttributeName and an AttributeValue for each attribute
//! @extraVarArgLim
//! @param ... Attribute names and values should follow as strings.
//! @inhtype{String,StringX} @slitToStr
//! @return The newly initialized XML tag
//! @endinternal
#if defined(RF_IAMHERE_FOR_DOXYGEN)
i_DECLIMEX_ RF_XMLTag* rfXMLTag_CreateLocal(RF_XMLTag* parent,void* name,void* content,unsigned char attrN,...);
#else
i_DECLIMEX_ RF_XMLTag* rfXMLTag_CreateLocalv(RF_XMLTag* parent,void* name,void* content,unsigned char attrN,...);
    #ifdef RF_OPTION_DEFAULT_ARGUMENTS
        #define rfXMLTag_CreateLocal(...)    RF_SELECT_FUNC_IF_NARGGT(i_NPSELECT_RF_XMLTAG_CREATELOCAL,4,__VA_ARGS__)
        #define i_NPSELECT_RF_XMLTAG_CREATELOCAL1(...)  RF_SELECT_FUNC_IF_NARGGT2(i_LIMSELECT_RF_XMLTAG_CREATELOCAL,18,__VA_ARGS__)
        #define i_NPSELECT_RF_XMLTAG_CREATELOCAL0(...)  RF_SELECT_FUNC(i_SELECT_RF_XMLTAG_CREATELOCAL,__VA_ARGS__)
        #define i_SELECT_RF_XMLTAG_CREATELOCAL3(i_PARENT_,i_NAME_,i_CONTENT_)   rfXMLTag_CreateLocalv(i_PARENT_,i_NAME_,i_CONTENT_,0)
        #define i_SELECT_RF_XMLTAG_CREATELOCAL2(i_PARENT_,i_NAME_)              rfXMLTag_CreateLocalv(i_PARENT_,i_NAME_,0,0)
        #define i_SELECT_RF_XMLTAG_CREATELOCAL1(...)    RF_COMPILE_ERROR("message \"Illegal Arguments Number: macro RFXML_() receives from 2 to N arguments\"")
        #define i_SELECT_RF_XMLTAG_CREATELOCAL0(...)    RF_COMPILE_ERROR("message \"Illegal Arguments Number: macro RFXML_() receives from 2 to N arguments\"")
        #define i_LIMSELECT_RF_XMLTAG_CREATELOCAL1(...) RF_COMPILE_ERROR("message \"Illegal Arguments Number: macro RFXML_() can't receive more than N arguments\"")
        #define i_LIMSELECT_RF_XMLTAG_CREATELOCAL0(...) RF_SELECT_FUNC(i_SELECT_RF_XMLTAG_CREATELOCAL,__VA_ARGS__)
        #define i_SELECT_RF_XMLTAG_CREATELOCAL4(...)   RF_COMPILE_ERROR("message \"Illegal Arguments Number: macro RFXML_() accepts from 2 to N arguments. But if 4 arguments are given then at least 2 more must follow\"")
        #define i_SELECT_RF_XMLTAG_CREATELOCAL5(...)   RF_COMPILE_ERROR("message \"Illegal Arguments Number: macro RFXML_() accepts from 2 to N arguments. But if 5 arguments are given then at least 1 more must follow\"")
        #define i_SELECT_RF_XMLTAG_CREATELOCAL6(i_PARENT_,i_NAME_,i_CONTENT_,i_ATTRN_,...) rfXMLTag_CreateLocalv(i_PARENT_,i_NAME_,i_CONTENT_,i_ATTRN_,__VA_ARGS__)
        #define i_SELECT_RF_XMLTAG_CREATELOCAL7(...)   RF_COMPILE_ERROR("message \"Illegal Arguments Number: macro RFXML_() needs an even number of extra arguments\"")
        #define i_SELECT_RF_XMLTAG_CREATELOCAL8(i_PARENT_,i_NAME_,i_CONTENT_,i_ATTRN_,...) i_rfLMS_WRAP8(RF_XMLTag*,rfXMLTag_CreateLocalv,i_PARENT_,i_NAME_,i_CONTENT_,i_RFUI8_(i_ATTRN_),__VA_ARGS__)
        #define i_SELECT_RF_XMLTAG_CREATELOCAL9(...)   RF_COMPILE_ERROR("message \"Illegal Arguments Number: macro RFXML_() needs an even number of extra arguments\"")
        #define i_SELECT_RF_XMLTAG_CREATELOCAL10(i_PARENT_,i_NAME_,i_CONTENT_,i_ATTRN_,...) i_rfLMS_WRAP10(RF_XMLTag*,rfXMLTag_CreateLocalv,i_PARENT_,i_NAME_,i_CONTENT_,i_RFUI8_(i_ATTRN_),__VA_ARGS__)
        #define i_SELECT_RF_XMLTAG_CREATELOCAL11(...)   RF_COMPILE_ERROR("message \"Illegal Arguments Number: macro RFXML_() needs an even number of extra arguments\"")
        #define i_SELECT_RF_XMLTAG_CREATELOCAL12(i_PARENT_,i_NAME_,i_CONTENT_,i_ATTRN_,...) i_rfLMS_WRAP12(RF_XMLTag*,rfXMLTag_CreateLocalv,i_PARENT_,i_NAME_,i_CONTENT_,i_RFUI8_(i_ATTRN_),__VA_ARGS__)
        #define i_SELECT_RF_XMLTAG_CREATELOCAL13(...)   RF_COMPILE_ERROR("message \"Illegal Arguments Number: macro RFXML_() needs an even number of extra arguments\"")
        #define i_SELECT_RF_XMLTAG_CREATELOCAL14(i_PARENT_,i_NAME_,i_CONTENT_,i_ATTRN_,...) i_rfLMS_WRAP14(RF_XMLTag*,rfXMLTag_CreateLocalv,i_PARENT_,i_NAME_,i_CONTENT_,i_RFUI8_(i_ATTRN_),__VA_ARGS__)
        #define i_SELECT_RF_XMLTAG_CREATELOCAL15(...)   RF_COMPILE_ERROR("message \"Illegal Arguments Number: macro RFXML_() needs an even number of extra arguments\"")
        #define i_SELECT_RF_XMLTAG_CREATELOCAL16(i_PARENT_,i_NAME_,i_CONTENT_,i_ATTRN_,...) i_rfLMS_WRAP16(RF_XMLTag*,rfXMLTag_CreateLocalv,i_PARENT_,i_NAME_,i_CONTENT_,i_RFUI8_(i_ATTRN_),__VA_ARGS__)
        #define i_SELECT_RF_XMLTAG_CREATELOCAL17(...)   RF_COMPILE_ERROR("message \"Illegal Arguments Number: macro RFXML_() needs an even number of extra arguments\"")
        #define i_SELECT_RF_XMLTAG_CREATELOCAL18(i_PARENT_,i_NAME_,i_CONTENT_,i_ATTRN_,...) i_rfLMS_WRAP18(RF_XMLTag*,rfXMLTag_CreateLocalv,i_PARENT_,i_NAME_,i_CONTENT_,i_RFUI8_(i_ATTRN_),__VA_ARGS__)
    #endif
#endif



//! @memberof RF_XMLTag
//! @brief Allocates and returns an XML Tag
//!
//! There are 2 versions of this function. If there are no @c DEFAULT_ARGUMENTS on then you should choose
//! the correct version yourself. @c rfXMLTag_Create2() only uses the name of the tag to create a new tag
//! while the @c rfXMLTag_Createv() function also accepts contents and attributes.
//!
//! If on the other hand the library has been compiled with @c DEFAULT_ARGUMENTS on as is recommended then
//! just by using this function @ref rfXMLTag_Create() and providing the appropriate number of arguments the
//! proper function will be chosen automatically.
//! @lmsFunction
//! @param parent A pointer to the parent tag of this tag
//! @param name Give the name of the tag as an @ref RF_String. @inhtype{String,StringX} @tmpSTR
//! @param content \rfoptional{0} An optional string with the tag's contents. If omitted
//! or if zero is given then the tag will have no content. @inhtype{String,StringX} @tmpSTR
//! @note if This parameter and the rest are omitted a more lightweight version of this function is called
//! @param attrN \rfoptional{0} The number of attributes this tag will have. The number you give here will basically
//! also be the number of additional arguments to follow. The additional arguments to follow should be @c attrN*2
//! an AttributeName and an AttributeValue for each attribute
//! @extraVarArgLim
//! @param ... Attribute names and values should follow as strings.
//! @inhtype{String,StringX} @tmpSTR
//! @return The newly initialized XML tag
#if defined(RF_IAMHERE_FOR_DOXYGEN)
i_DECLIMEX_ RF_XMLTag* rfXMLTag_Create(RF_XMLTag* parent,void* name,void* content,unsigned char attrN,...);
#else
i_DECLIMEX_ RF_XMLTag* rfXMLTag_Create2(RF_XMLTag* parent,void* name);
i_DECLIMEX_ RF_XMLTag* rfXMLTag_Createv(RF_XMLTag* parent,void* name,void* content,unsigned char* attrN,...);
    #ifdef RF_OPTION_DEFAULT_ARGUMENTS
        #define rfXMLTag_Create(...)    RF_SELECT_FUNC_IF_NARGGT(i_NPSELECT_RF_XMLTAG_CREATE,4,__VA_ARGS__)
        #define i_NPSELECT_RF_XMLTAG_CREATE1(...)  RF_SELECT_FUNC_IF_NARGGT2(i_LIMSELECT_RF_XMLTAG_CREATE,18,__VA_ARGS__)
        #define i_NPSELECT_RF_XMLTAG_CREATE0(...)  RF_SELECT_FUNC(i_SELECT_RF_XMLTAG_CREATE,__VA_ARGS__)
        #define i_SELECT_RF_XMLTAG_CREATE3(i_PARENT_,i_NAME_,i_CONTENT_)   i_rfLMS_WRAP4(RF_XMLTag*,rfXMLTag_Createv,i_PARENT_,i_NAME_,i_CONTENT_,i_RFUI8_(0))
        #define i_SELECT_RF_XMLTAG_CREATE2(i_PARENT_,i_NAME_)               i_rfLMS_WRAP2(RF_XMLTag*,rfXMLTag_Create2,i_PARENT_,i_NAME_)
        #define i_SELECT_RF_XMLTAG_CREATE1(...)    RF_COMPILE_ERROR("message \"Illegal Arguments Number: Function rfXMLTag_Create() receives from 2 to N arguments\"")
        #define i_SELECT_RF_XMLTAG_CREATE0(...)    RF_COMPILE_ERROR("message \"Illegal Arguments Number: Function rfXMLTag_Create() receives from 2 to N arguments\"")
        #define i_LIMSELECT_RF_XMLTAG_CREATE1(...) RF_COMPILE_ERROR("message \"Illegal Arguments Number: Function rfXMLTag_Create() can't receive more than N arguments\"")
        #define i_LIMSELECT_RF_XMLTAG_CREATE0(...) RF_SELECT_FUNC(i_SELECT_RF_XMLTAG_CREATE,__VA_ARGS__)
        #define i_SELECT_RF_XMLTAG_CREATE4(...)   RF_COMPILE_ERROR("message \"Illegal Arguments Number: Function rfXMLTag_Create() accepts from 2 to N arguments. But if 4 arguments are given then at least 2 more must follow\"")
        #define i_SELECT_RF_XMLTAG_CREATE5(...)   RF_COMPILE_ERROR("message \"Illegal Arguments Number: Function rfXMLTag_Create() accepts from 2 to N arguments. But if 5 arguments are given then at least 1 more must follow\"")
        #define i_SELECT_RF_XMLTAG_CREATE6(i_PARENT_,i_NAME_,i_CONTENT_,i_ATTRN_,...)  i_rfLMS_WRAP6(RF_XMLTag*,rfXMLTag_Createv,i_PARENT_,i_NAME_,i_CONTENT_,i_RFUI8_(i_ATTRN_),__VA_ARGS__)
        #define i_SELECT_RF_XMLTAG_CREATE7(...)   RF_COMPILE_ERROR("message \"Illegal Arguments Number: Function rfXMLTag_Create() needs an even number of extra arguments\"")
        #define i_SELECT_RF_XMLTAG_CREATE8(i_PARENT_,i_NAME_,i_CONTENT_,i_ATTRN_,...) i_rfLMS_WRAP8(RF_XMLTag*,rfXMLTag_Createv,i_PARENT_,i_NAME_,i_CONTENT_,i_RFUI8_(i_ATTRN_),__VA_ARGS__)
        #define i_SELECT_RF_XMLTAG_CREATE9(...)   RF_COMPILE_ERROR("message \"Illegal Arguments Number: Function rfXMLTag_Create() needs an even number of extra arguments\"")
        #define i_SELECT_RF_XMLTAG_CREATE10(i_PARENT_,i_NAME_,i_CONTENT_,i_ATTRN_,...) i_rfLMS_WRAP10(RF_XMLTag*,rfXMLTag_Createv,i_PARENT_,i_NAME_,i_CONTENT_,i_RFUI8_(i_ATTRN_),__VA_ARGS__)
        #define i_SELECT_RF_XMLTAG_CREATE11(...)   RF_COMPILE_ERROR("message \"Illegal Arguments Number: Function rfXMLTag_Create() needs an even number of extra arguments\"")
        #define i_SELECT_RF_XMLTAG_CREATE12(i_PARENT_,i_NAME_,i_CONTENT_,i_ATTRN_,...) i_rfLMS_WRAP12(RF_XMLTag*,rfXMLTag_Createv,i_PARENT_,i_NAME_,i_CONTENT_,i_RFUI8_(i_ATTRN_),__VA_ARGS__)
        #define i_SELECT_RF_XMLTAG_CREATE13(...)   RF_COMPILE_ERROR("message \"Illegal Arguments Number: Function rfXMLTag_Create() needs an even number of extra arguments\"")
        #define i_SELECT_RF_XMLTAG_CREATE14(i_PARENT_,i_NAME_,i_CONTENT_,i_ATTRN_,...) i_rfLMS_WRAP14(RF_XMLTag*,rfXMLTag_Createv,i_PARENT_,i_NAME_,i_CONTENT_,i_RFUI8_(i_ATTRN_),__VA_ARGS__)
        #define i_SELECT_RF_XMLTAG_CREATE15(...)   RF_COMPILE_ERROR("message \"Illegal Arguments Number: Function rfXMLTag_Create() needs an even number of extra arguments\"")
        #define i_SELECT_RF_XMLTAG_CREATE16(i_PARENT_,i_NAME_,i_CONTENT_,i_ATTRN_,...) i_rfLMS_WRAP16(RF_XMLTag*,rfXMLTag_Createv,i_PARENT_,i_NAME_,i_CONTENT_,i_RFUI8_(i_ATTRN_),__VA_ARGS__)
        #define i_SELECT_RF_XMLTAG_CREATE17(...)   RF_COMPILE_ERROR("message \"Illegal Arguments Number: Function rfXMLTag_Create() needs an even number of extra arguments\"")
        #define i_SELECT_RF_XMLTAG_CREATE18(i_PARENT_,i_NAME_,i_CONTENT_,i_ATTRN_,...) i_rfLMS_WRAP18(RF_XMLTag*,rfXMLTag_Createv,i_PARENT_,i_NAME_,i_CONTENT_,i_RFUI8_(i_ATTRN_),__VA_ARGS__)
    #endif
#endif
//! @memberof RF_XMLTag
//! @brief Initializes an XML Tag
//!
//! There are 2 versions of this function. If there are no @c DEFAULT_ARGUMENTS on then you should choose
//! the correct version yourself. @c rfXMLTag_Init3() only uses the name of the tag to create a new tag
//! while the @c rfXMLTag_Initv() function also accepts contents and attributes.
//!
//! If on the other hand the library has been compiled with @c DEFAULT_ARGUMENTS on as is recommended then
//! just by using this function @ref rfXMLTag_Init() and providing the appropriate number of arguments the
//! proper function will be chosen automatically.
//! @lmsFunction
//! @param parent A pointer to the parent tag of this tag
//! @param name Give the name of the tag as an @ref RF_String. @inhtype{String,StringX} @tmpSTR
//! @param content \rfoptional{0} An optional string with the tag's contents. If omitted
//! or if zero is given then the tag will have no content. @inhtype{String,StringX} @tmpSTR
//! @note if This parameter and the rest are omitted a more lightweight version of this function is called
//! @param attrN \rfoptional{0} The number of attributes this tag will have. The number you give here will basically
//! also be the number of additional arguments to follow. The additional arguments to follow should be @c attrN*2
//! an AttributeName and an AttributeValue for each attribute
//! @extraVarArgLim
//! @param ... Attribute names and values should follow as strings.
//! @inhtype{String,StringX} @tmpSTR
//! @return true for success and false otherwise
#if defined(RF_IAMHERE_FOR_DOXYGEN)
i_DECLIMEX_ char rfXMLTag_Init(RF_XMLTag* x,RF_XMLTag* parent,void* name);
#else
i_DECLIMEX_ char rfXMLTag_Init3(RF_XMLTag* x,RF_XMLTag* parent,void* name);
i_DECLIMEX_ char rfXMLTag_Initv(RF_XMLTag* x,RF_XMLTag* parent,void* name,void* content,unsigned char* attrN,...);
    #ifdef RF_OPTION_DEFAULT_ARGUMENTS
        #define rfXMLTag_Init(...)    RF_SELECT_FUNC_IF_NARGGT(i_NPSELECT_RF_XMLTAG_INIT,5,__VA_ARGS__)
        #define i_NPSELECT_RF_XMLTAG_INIT1(...)  RF_SELECT_FUNC_IF_NARGGT2(i_LIMSELECT_RF_XMLTAG_INIT,18,__VA_ARGS__)
        #define i_NPSELECT_RF_XMLTAG_INIT0(...)  RF_SELECT_FUNC(i_SELECT_RF_XMLTAG_INIT,__VA_ARGS__)
        #define i_SELECT_RF_XMLTAG_INIT4(i_TAG_,i_PARENT_,i_NAME_,i_CONTENT_)    i_rfLMSX_WRAP4(char,rfXMLTag_Initv,i_TAG_,i_PARENT_,i_NAME_,i_CONTENT_,i_RFUI8_(0))
        #define i_SELECT_RF_XMLTAG_INIT3(i_TAG_,i_PARENT_,i_NAME_)    i_rfLMSX_WRAP3(char,rfXMLTag_Init3,i_TAG_,i_PARENT_,i_NAME_)
        #define i_SELECT_RF_XMLTAG_INIT2(...)   RF_COMPILE_ERROR("message \"Illegal Arguments Number: Function rfXMLTag_Init() receives from 3 to N arguments arguments\"")
        #define i_SELECT_RF_XMLTAG_INIT1(...)   RF_COMPILE_ERROR("message \"Illegal Arguments Number: Function rfXMLTag_Init() receives from 3 to N arguments arguments\"")
        #define i_SELECT_RF_XMLTAG_INIT0(...)   RF_COMPILE_ERROR("message \"Illegal Arguments Number: Function rfXMLTag_Init() receives from 3 to N arguments arguments\"")
        #define i_LIMSELECT_RF_XMLTAG_INIT1(...) RF_COMPILE_ERROR("message \"Illegal Arguments Number: Function rfXMLTag_Init() can't receive more than N arguments\"")
        #define i_LIMSELECT_RF_XMLTAG_INIT0(...) RF_SELECT_FUNC(i_SELECT_RF_XMLTAG_INIT,__VA_ARGS__)
        #define i_SELECT_RF_XMLTAG_INIT5(...)   RF_COMPILE_ERROR("message \"Illegal Arguments Number: Function rfXMLTag_Init() accepts from 3 to N arguments. But if 5 arguments are given then at least 2 more must follow\"")
        #define i_SELECT_RF_XMLTAG_INIT6(...)   RF_COMPILE_ERROR("message \"Illegal Arguments Number: Function rfXMLTag_Init() accepts from 3 to N arguments. But if 6 arguments are given then at least 1 more must follow\"")
        #define i_SELECT_RF_XMLTAG_INIT7(i_TAG_,i_PARENT_,i_NAME_,i_CONTENT_,i_ATTRN_,...) i_rfLMSX_WRAP7(char,rfXMLTag_Initv,i_TAG_,i_PARENT_,i_NAME_,i_CONTENT_,i_RFUI8_(i_ATTRN_),__VA_ARGS__)
        #define i_SELECT_RF_XMLTAG_INIT8(...)  RF_COMPILE_ERROR("message \"Illegal Arguments Number: Function rfXMLTag_Init() acepts an even number of extra arguments\"")
        #define i_SELECT_RF_XMLTAG_INIT9(i_TAG_,i_PARENT_,i_NAME_,i_CONTENT_,i_ATTRN_,...) i_rfLMSX_WRAP9(char,rfXMLTag_Initv,i_TAG_,i_PARENT_,i_NAME_,i_CONTENT_,i_RFUI8_(i_ATTRN_),__VA_ARGS__)
        #define i_SELECT_RF_XMLTAG_INIT10(...)  RF_COMPILE_ERROR("message \"Illegal Arguments Number: Function rfXMLTag_Init() acepts an even number of extra arguments\"")
        #define i_SELECT_RF_XMLTAG_INIT11(i_TAG_,i_PARENT_,i_NAME_,i_CONTENT_,i_ATTRN_,...) i_rfLMSX_WRAP11(char,rfXMLTag_Initv,i_TAG_,i_PARENT_,i_NAME_,i_CONTENT_,i_RFUI8_(i_ATTRN_),__VA_ARGS__)
        #define i_SELECT_RF_XMLTAG_INIT12(...)  RF_COMPILE_ERROR("message \"Illegal Arguments Number: Function rfXMLTag_Init() acepts an even number of extra arguments\"")
        #define i_SELECT_RF_XMLTAG_INIT13(i_TAG_,i_PARENT_,i_NAME_,i_CONTENT_,i_ATTRN_,...) i_rfLMSX_WRAP13(char,rfXMLTag_Initv,i_TAG_,i_PARENT_,i_NAME_,i_CONTENT_,i_RFUI8_(i_ATTRN_),__VA_ARGS__)
        #define i_SELECT_RF_XMLTAG_INIT14(...)  RF_COMPILE_ERROR("message \"Illegal Arguments Number: Function rfXMLTag_Init() acepts an even number of extra arguments\"")
        #define i_SELECT_RF_XMLTAG_INIT15(i_TAG_,i_PARENT_,i_NAME_,i_CONTENT_,i_ATTRN_,...) i_rfLMSX_WRAP15(char,rfXMLTag_Initv,i_TAG_,i_PARENT_,i_NAME_,i_CONTENT_,i_RFUI8_(i_ATTRN_),__VA_ARGS__)
        #define i_SELECT_RF_XMLTAG_INIT16(...)  RF_COMPILE_ERROR("message \"Illegal Arguments Number: Function rfXMLTag_Init() acepts an even number of extra arguments\"")
        #define i_SELECT_RF_XMLTAG_INIT17(i_TAG_,i_PARENT_,i_NAME_,i_CONTENT_,i_ATTRN_,...) i_rfLMSX_WRAP17(char,rfXMLTag_Initv,i_TAG_,i_PARENT_,i_NAME_,i_CONTENT_,i_RFUI8_(i_ATTRN_),__VA_ARGS__)
        #define i_SELECT_RF_XMLTAG_INIT18(...)  RF_COMPILE_ERROR("message \"Illegal Arguments Number: Function rfXMLTag_Init() acepts an even number of extra arguments\"")
    #endif
#endif




//! @memberof RF_XMLTag
//! @brief Copies XML Tag @c src to XML Tag @c dst
//!
//! @param dst The XMLTag copy we are creating
//! @param src The XMLTag that we are copying
i_DECLIMEX_ void rfXMLTag_Copy_IN(RF_XMLTag* dst,RF_XMLTag* src);
//! @memberof RF_XMLTag
//! @brief Allocates and returns a copy of the given XML Tag
//!
//! @param src The XMLTag that we are copying
//! @return Returns an allocated copy of the @c src XML tag
i_DECLIMEX_ RF_XMLTag* rfXMLTag_Copy_OUT(RF_XMLTag* src);

//! @memberof RF_XMLTag
//! @brief Destroys an XML tag
//!
//! Use it for xml tags made by _Create
//! @param t The tag to destroy
i_DECLIMEX_ void rfXMLTag_Destroy(RF_XMLTag* t);
//! @memberof RF_XMLTag
//! @brief Deinitializes an XML tag
//!
//! Use it for xml tags made by _Init
//! @param t The tag to destroy
i_DECLIMEX_ void rfXMLTag_Deinit(RF_XMLTag* t);

//! @memberof RF_XMLTag
//! @brief Adds a child tag by first making an internal copy of the tag
//!
//! The child tag is copied inside the function. The
//! user can free it right afterwards
//! @param t The tag
//! @param c The child tag to add. A copy of it is made inside the function and added to the XML tag @c t. The user can free the passed tag after the function.
i_DECLIMEX_ void rfXMLTag_AddTag(RF_XMLTag* t,RF_XMLTag* c);

//! @memberof RF_XMLTag
//! @brief Adds a child tag without making an internal copy
//!
//! The child tag is <b>NOT</b> copied inside the function. The
//! user should not mess with the child tag after the function call
//! because that would probably destroy the xml tree.
//! @param t The tag
//! @param c The child tag to add. A copy of it is made inside the function and added to the XML tag @c t. The user can free the passed tag after the function.
i_DECLIMEX_ void rfXMLTag_AddTag_nocopy(RF_XMLTag* t,RF_XMLTag* c);

//! @memberof RF_XMLTag
//! @brief Adds an attribute to the tag
//!
//! To add an attribute to the tag, an attribute name and an attribute value are required. These can be in the form of either an RF_String or RF_StringX.
//! Both strins are copied internally in the function so there is no need to worry about freeing them later.
//! @lmsFunction
//! @param t The tag
//! @param attribName Give the name of the attribute as an @ref RF_String. @inhtype{String,StringX} @tmpSTR
//! @param attribValue Give the value of the attribute as an @ref RF_String. @inhtype{String,StringX} @tmpSTR
#if defined(RF_IAMHERE_FOR_DOXYGEN)
i_DECLIMEX_ void rfXMLTag_AddAttribute(RF_XMLTag* t,void* attribName,void* attribValue);
#else
i_DECLIMEX_ void i_rfXMLTag_AddAttribute(RF_XMLTag* t,void* attribName,void* attribValue);
#define rfXMLTag_AddAttribute(i_THISTAG_,i_ATTRIBNAME_,i_ATTRIBVALUE_) i_rfLMS_WRAP3(void,i_rfXMLTag_AddAttribute,i_THISTAG_,i_ATTRIBNAME_,i_ATTRIBVALUE_)
#endif

//! @memberof RF_XMLTag
//! @brief Adds contents to the tag
//!
//! @lmsFunction
//! @param t The tag
//! @param c Give an @ref RF_String to add as contents to the tag. An internal
//! copy of the String is made, so there is no need to worry about freeing it later. @inhtype{String,StringX} @tmpSTR
#if defined(RF_IAMHERE_FOR_DOXYGEN)
i_DECLIMEX_ void rfXMLTag_AddContent(RF_XMLTag* t,void* content);
#else
i_DECLIMEX_ void i_rfXMLTag_AddContent(RF_XMLTag* t,void* content);
#define rfXMLTag_AddContent(i_THISTAG_,i_CONTENT_)  i_rfLMS_WRAP2(void,i_rfXMLTag_AddContent,i_THISTAG_,i_CONTENT_)
#endif

//! @memberof RF_XMLTag
//! @brief Gets a particular child tag
//!
//! @param t The tag
//! @param i The child index
//! @return a pointer to the child tag or 0 if child does not exist. The returned pointer points to the tag inside the XML handler and needs not be freed.
i_DECLIMEX_ RF_XMLTag* rfXMLTag_GetChild(RF_XMLTag* t,uint32_t i);
//! @memberof RF_XMLTag
//! @brief Removes a particular child tag
//!
//! Removes a child tag from this tag recursively destroying its own children
//! in the process. If the index given is out of bounds, nothing happens.
//! @param t This tag
//! @param i The child index
i_DECLIMEX_ void rfXMLTag_RemoveChild(RF_XMLTag* t,uint32_t i);

//! @memberof RF_XMLTag
//! @brief Gets a particular attribute name
//!
//! This function creates a copy of the String so the string has to be freed by the user later.
//! @param[in] t The tag
//! @param[in] i The attribute index
//! @param[out] name Pass an RF_String upon which the attribute name will be @b copied.
//! @return true if the name of the attribute got copied to the String given at @c name or false otherwise.
i_DECLIMEX_ char rfXMLTag_GetAttributeName(RF_XMLTag* t,uint32_t i,RF_String* name);

//! @memberof RF_XMLTag
//! @brief Gets a particular attribute value
//!
//! This function creates a copy of the String so the string has to be freed by the user later.
//! @param[in] t The tag
//! @param[in] i The attribute index
//! @param[out] value Pass an RF_String upon which the attribute value will be @b copied.
//! @return true if the value of the attribute got copied to the String given at @c value or false otherwise.
i_DECLIMEX_ char rfXMLTag_GetAttributeValue(RF_XMLTag* t,uint32_t i,RF_String* value);

//! @memberof RF_XMLTag
//! @brief Gets the tag's content as an RF_String
//!
//! This function creates a copy of the String so the string has to be freed by the user later.
//! @param[in] t The tag
//! @param[out] line Pass an RF_String upon which the content line will be @b copied.
i_DECLIMEX_ void rfXMLTag_GetContent(RF_XMLTag* t,RF_String* line);

//! @memberof RF_XMLTag
//! @brief Turns the tag into a string
//!
//! Reads all of the xml subtree from this tag to all its children and then outputs it
//! into the given @ref RF_StringX.
//! @param[in] t The tag
//! @param[out] s Give an @ref RF_StringX here to hold the outputting of the given @c t XML tag
//! into a string
//! @return Returns @c true for success or @c false if there was an error
i_DECLIMEX_ char rfXMLTag_ToStr(RF_XMLTag *t ,RF_StringX* s);
#ifdef __cplusplus
}///closing bracket for calling from C++
#endif

#else
    #error Attempted to include Refu XML module without the proper module flag on. If you need to use it build the library with that option.
#endif//XML module check stop

#endif//include guards end
