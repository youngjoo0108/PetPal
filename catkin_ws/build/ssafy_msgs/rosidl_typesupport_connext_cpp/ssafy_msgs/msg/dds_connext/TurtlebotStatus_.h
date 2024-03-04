

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from TurtlebotStatus_.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef TurtlebotStatus__1063517911_h
#define TurtlebotStatus__1063517911_h

#ifndef NDDS_STANDALONE_TYPE
#ifndef ndds_cpp_h
#include "ndds/ndds_cpp.h"
#endif
#else
#include "ndds_standalone_type.h"
#endif

#include "geometry_msgs/msg/dds_connext/Twist_.h"
namespace ssafy_msgs {
    namespace msg {
        namespace dds_ {

            extern const char *TurtlebotStatus_TYPENAME;

            struct TurtlebotStatus_Seq;
            #ifndef NDDS_STANDALONE_TYPE
            class TurtlebotStatus_TypeSupport;
            class TurtlebotStatus_DataWriter;
            class TurtlebotStatus_DataReader;
            #endif

            class TurtlebotStatus_ 
            {
              public:
                typedef struct TurtlebotStatus_Seq Seq;
                #ifndef NDDS_STANDALONE_TYPE
                typedef TurtlebotStatus_TypeSupport TypeSupport;
                typedef TurtlebotStatus_DataWriter DataWriter;
                typedef TurtlebotStatus_DataReader DataReader;
                #endif

                geometry_msgs::msg::dds_::Twist_   twist_ ;
                DDS_Octet   power_supply_status_ ;
                DDS_Float   battery_percentage_ ;
                DDS_Boolean   can_use_hand_ ;
                DDS_Boolean   can_put_ ;
                DDS_Boolean   can_lift_ ;

            };
            #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT_ssafy_msgs)
            /* If the code is building on Windows, start exporting symbols.
            */
            #undef NDDSUSERDllExport
            #define NDDSUSERDllExport __declspec(dllexport)
            #endif

            NDDSUSERDllExport DDS_TypeCode* TurtlebotStatus__get_typecode(void); /* Type code */

            DDS_SEQUENCE(TurtlebotStatus_Seq, TurtlebotStatus_);

            NDDSUSERDllExport
            RTIBool TurtlebotStatus__initialize(
                TurtlebotStatus_* self);

            NDDSUSERDllExport
            RTIBool TurtlebotStatus__initialize_ex(
                TurtlebotStatus_* self,RTIBool allocatePointers,RTIBool allocateMemory);

            NDDSUSERDllExport
            RTIBool TurtlebotStatus__initialize_w_params(
                TurtlebotStatus_* self,
                const struct DDS_TypeAllocationParams_t * allocParams);  

            NDDSUSERDllExport
            void TurtlebotStatus__finalize(
                TurtlebotStatus_* self);

            NDDSUSERDllExport
            void TurtlebotStatus__finalize_ex(
                TurtlebotStatus_* self,RTIBool deletePointers);

            NDDSUSERDllExport
            void TurtlebotStatus__finalize_w_params(
                TurtlebotStatus_* self,
                const struct DDS_TypeDeallocationParams_t * deallocParams);

            NDDSUSERDllExport
            void TurtlebotStatus__finalize_optional_members(
                TurtlebotStatus_* self, RTIBool deletePointers);  

            NDDSUSERDllExport
            RTIBool TurtlebotStatus__copy(
                TurtlebotStatus_* dst,
                const TurtlebotStatus_* src);

            #if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT_ssafy_msgs)
            /* If the code is building on Windows, stop exporting symbols.
            */
            #undef NDDSUSERDllExport
            #define NDDSUSERDllExport
            #endif
        } /* namespace dds_  */
    } /* namespace msg  */
} /* namespace ssafy_msgs  */

#endif /* TurtlebotStatus_ */

