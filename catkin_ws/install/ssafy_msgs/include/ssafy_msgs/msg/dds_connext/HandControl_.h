

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from HandControl_.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef HandControl__1586745787_h
#define HandControl__1586745787_h

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

            extern const char *HandControl_TYPENAME;

            struct HandControl_Seq;
            #ifndef NDDS_STANDALONE_TYPE
            class HandControl_TypeSupport;
            class HandControl_DataWriter;
            class HandControl_DataReader;
            #endif

            class HandControl_ 
            {
              public:
                typedef struct HandControl_Seq Seq;
                #ifndef NDDS_STANDALONE_TYPE
                typedef HandControl_TypeSupport TypeSupport;
                typedef HandControl_DataWriter DataWriter;
                typedef HandControl_DataReader DataReader;
                #endif

                DDS_Octet   control_mode_ ;
                DDS_Float   put_distance_ ;
                DDS_Float   put_height_ ;

            };
            #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT_ssafy_msgs)
            /* If the code is building on Windows, start exporting symbols.
            */
            #undef NDDSUSERDllExport
            #define NDDSUSERDllExport __declspec(dllexport)
            #endif

            NDDSUSERDllExport DDS_TypeCode* HandControl__get_typecode(void); /* Type code */

            DDS_SEQUENCE(HandControl_Seq, HandControl_);

            NDDSUSERDllExport
            RTIBool HandControl__initialize(
                HandControl_* self);

            NDDSUSERDllExport
            RTIBool HandControl__initialize_ex(
                HandControl_* self,RTIBool allocatePointers,RTIBool allocateMemory);

            NDDSUSERDllExport
            RTIBool HandControl__initialize_w_params(
                HandControl_* self,
                const struct DDS_TypeAllocationParams_t * allocParams);  

            NDDSUSERDllExport
            void HandControl__finalize(
                HandControl_* self);

            NDDSUSERDllExport
            void HandControl__finalize_ex(
                HandControl_* self,RTIBool deletePointers);

            NDDSUSERDllExport
            void HandControl__finalize_w_params(
                HandControl_* self,
                const struct DDS_TypeDeallocationParams_t * deallocParams);

            NDDSUSERDllExport
            void HandControl__finalize_optional_members(
                HandControl_* self, RTIBool deletePointers);  

            NDDSUSERDllExport
            RTIBool HandControl__copy(
                HandControl_* dst,
                const HandControl_* src);

            #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT_ssafy_msgs)
            /* If the code is building on Windows, stop exporting symbols.
            */
            #undef NDDSUSERDllExport
            #define NDDSUSERDllExport
            #endif
        } /* namespace dds_  */
    } /* namespace msg  */
} /* namespace ssafy_msgs  */

#endif /* HandControl_ */

