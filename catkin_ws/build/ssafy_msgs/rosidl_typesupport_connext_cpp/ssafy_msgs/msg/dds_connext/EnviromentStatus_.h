

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from EnviromentStatus_.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef EnviromentStatus__1729437768_h
#define EnviromentStatus__1729437768_h

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

            extern const char *EnviromentStatus_TYPENAME;

            struct EnviromentStatus_Seq;
            #ifndef NDDS_STANDALONE_TYPE
            class EnviromentStatus_TypeSupport;
            class EnviromentStatus_DataWriter;
            class EnviromentStatus_DataReader;
            #endif

            class EnviromentStatus_ 
            {
              public:
                typedef struct EnviromentStatus_Seq Seq;
                #ifndef NDDS_STANDALONE_TYPE
                typedef EnviromentStatus_TypeSupport TypeSupport;
                typedef EnviromentStatus_DataWriter DataWriter;
                typedef EnviromentStatus_DataReader DataReader;
                #endif

                DDS_Octet   month_ ;
                DDS_Octet   day_ ;
                DDS_Octet   hour_ ;
                DDS_Octet   minute_ ;
                DDS_Octet   temperature_ ;
                DDS_Char *   weather_ ;

            };
            #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT_ssafy_msgs)
            /* If the code is building on Windows, start exporting symbols.
            */
            #undef NDDSUSERDllExport
            #define NDDSUSERDllExport __declspec(dllexport)
            #endif

            NDDSUSERDllExport DDS_TypeCode* EnviromentStatus__get_typecode(void); /* Type code */

            DDS_SEQUENCE(EnviromentStatus_Seq, EnviromentStatus_);

            NDDSUSERDllExport
            RTIBool EnviromentStatus__initialize(
                EnviromentStatus_* self);

            NDDSUSERDllExport
            RTIBool EnviromentStatus__initialize_ex(
                EnviromentStatus_* self,RTIBool allocatePointers,RTIBool allocateMemory);

            NDDSUSERDllExport
            RTIBool EnviromentStatus__initialize_w_params(
                EnviromentStatus_* self,
                const struct DDS_TypeAllocationParams_t * allocParams);  

            NDDSUSERDllExport
            void EnviromentStatus__finalize(
                EnviromentStatus_* self);

            NDDSUSERDllExport
            void EnviromentStatus__finalize_ex(
                EnviromentStatus_* self,RTIBool deletePointers);

            NDDSUSERDllExport
            void EnviromentStatus__finalize_w_params(
                EnviromentStatus_* self,
                const struct DDS_TypeDeallocationParams_t * deallocParams);

            NDDSUSERDllExport
            void EnviromentStatus__finalize_optional_members(
                EnviromentStatus_* self, RTIBool deletePointers);  

            NDDSUSERDllExport
            RTIBool EnviromentStatus__copy(
                EnviromentStatus_* dst,
                const EnviromentStatus_* src);

            #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT_ssafy_msgs)
            /* If the code is building on Windows, stop exporting symbols.
            */
            #undef NDDSUSERDllExport
            #define NDDSUSERDllExport
            #endif
        } /* namespace dds_  */
    } /* namespace msg  */
} /* namespace ssafy_msgs  */

#endif /* EnviromentStatus_ */

