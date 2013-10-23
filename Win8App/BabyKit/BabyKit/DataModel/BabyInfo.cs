using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace BabyKit.DataModel
{
    [DataContract]
    class BabyInfo
    {
        [DataMember]
        internal string Name;

        // TODO convert it to an array
        [DataMember]
        internal string NickName;

        [DataMember]
        internal DateTime Birthday;
    }
}
