

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from CustomObjectInfo_.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef CustomObjectInfo__1496429073_h
#define CustomObjectInfo__1496429073_h

#ifndef NDDS_STANDALONE_TYPE
#ifndef ndds_cpp_h
#include "ndds/ndds_cpp.h"
#endif
#else
#include "ndds_standalone_type.h"
#endif

#include "geometry_msgs/msg/dds_connext/Vector3_.h"
namespace ssafy_msgs {
    namespace msg {
        namespace dds_ {

            extern const char *CustomObjectInfo_TYPENAME;

            struct CustomObjectInfo_Seq;
            #ifndef NDDS_STANDALONE_TYPE
            class CustomObjectInfo_TypeSupport;
            class CustomObjectInfo_DataWriter;
            class CustomObjectInfo_DataReader;
            #endif

            class CustomObjectInfo_ 
            {
              public:
                typedef struct CustomObjectInfo_Seq Seq;
                #ifndef NDDS_STANDALONE_TYPE
                typedef CustomObjectInfo_TypeSupport TypeSupport;
                typedef CustomObjectInfo_DataWriter DataWriter;
                typedef CustomObjectInfo_DataReader DataReader;
                #endif

                geometry_msgs::msg::dds_::Vector3_Seq  position_ ;

            };
            #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT_ssafy_msgs)
            /* If the code is building on Windows, start exporting symbols.
            */
            #undef NDDSUSERDllExport
            #define NDDSUSERDllExport __declspec(dllexport)
            #endif

            NDDSUSERDllExport DDS_TypeCode* CustomObjectInfo__get_typecode(void); /* Type code */

            DDS_SEQUENCE(CustomObjectInfo_Seq, CustomObjectInfo_);

            NDDSUSERDllExport
            RTIBool CustomObjectInfo__initialize(
                CustomObjectInfo_* self);

            NDDSUSERDllExport
            RTIBool CustomObjectInfo__initialize_ex(
                CustomObjectInfo_* self,RTIBool allocatePointers,RTIBool allocateMemory);

            NDDSUSERDllExport
            RTIBool CustomObjectInfo__initialize_w_params(
                CustomObjectInfo_* self,
                const struct DDS_TypeAllocationParams_t * allocParams);  

            NDDSUSERDllExport
            void CustomObjectInfo__finalize(
                CustomObjectInfo_* self);

            NDDSUSERDllExport
            void CustomObjectInfo__finalize_ex(
                CustomObjectInfo_* self,RTIBool deletePointers);

            NDDSUSERDllExport
            void CustomObjectInfo__finalize_w_params(
                CustomObjectInfo_* self,
                const struct DDS_TypeDeallocationParams_t * deallocParams);

            NDDSUSERDllExport
            void CustomObjectInfo__finalize_optional_members(
                CustomObjectInfo_* self, RTIBool deletePointers);  

            NDDSUSERDllExport
            RTIBool CustomObjectInfo__copy(
                CustomObjectInfo_* dst,
                const CustomObjectInfo_* src);

            #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT_ssafy_msgs)
            /* If the code is building on Windows, stop exporting symbols.
            */
            #undef NDDSUSERDllExport
            #define NDDSUSERDllExport
            #endif
        } /* namespace dds_  */
    } /* namespace msg  */
} /* namespace ssafy_msgs  */

#endif /* CustomObjectInfo_ */

