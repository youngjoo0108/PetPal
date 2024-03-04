

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Num_.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef Num__1826213104_h
#define Num__1826213104_h

#ifndef NDDS_STANDALONE_TYPE
#ifndef ndds_cpp_h
#include "ndds/ndds_cpp.h"
#endif
#else
#include "ndds_standalone_type.h"
#endif

namespace ssafy_msgs {
    namespace msg {
        namespace dds_ {

            extern const char *Num_TYPENAME;

            struct Num_Seq;
            #ifndef NDDS_STANDALONE_TYPE
            class Num_TypeSupport;
            class Num_DataWriter;
            class Num_DataReader;
            #endif

            class Num_ 
            {
              public:
                typedef struct Num_Seq Seq;
                #ifndef NDDS_STANDALONE_TYPE
                typedef Num_TypeSupport TypeSupport;
                typedef Num_DataWriter DataWriter;
                typedef Num_DataReader DataReader;
                #endif

                DDS_LongLong   num_ ;
                DDS_Boolean   air_ ;
                DDS_Boolean   door_ ;

            };
            #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT_ssafy_msgs)
            /* If the code is building on Windows, start exporting symbols.
            */
            #undef NDDSUSERDllExport
            #define NDDSUSERDllExport __declspec(dllexport)
            #endif

            NDDSUSERDllExport DDS_TypeCode* Num__get_typecode(void); /* Type code */

            DDS_SEQUENCE(Num_Seq, Num_);

            NDDSUSERDllExport
            RTIBool Num__initialize(
                Num_* self);

            NDDSUSERDllExport
            RTIBool Num__initialize_ex(
                Num_* self,RTIBool allocatePointers,RTIBool allocateMemory);

            NDDSUSERDllExport
            RTIBool Num__initialize_w_params(
                Num_* self,
                const struct DDS_TypeAllocationParams_t * allocParams);  

            NDDSUSERDllExport
            void Num__finalize(
                Num_* self);

            NDDSUSERDllExport
            void Num__finalize_ex(
                Num_* self,RTIBool deletePointers);

            NDDSUSERDllExport
            void Num__finalize_w_params(
                Num_* self,
                const struct DDS_TypeDeallocationParams_t * deallocParams);

            NDDSUSERDllExport
            void Num__finalize_optional_members(
                Num_* self, RTIBool deletePointers);  

            NDDSUSERDllExport
            RTIBool Num__copy(
                Num_* dst,
                const Num_* src);

            #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT_ssafy_msgs)
            /* If the code is building on Windows, stop exporting symbols.
            */
            #undef NDDSUSERDllExport
            #define NDDSUSERDllExport
            #endif
        } /* namespace dds_  */
    } /* namespace msg  */
} /* namespace ssafy_msgs  */

#endif /* Num_ */

