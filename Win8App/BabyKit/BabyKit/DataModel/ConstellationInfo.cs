using BabyKit.Utility;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;
using Windows.Storage;

namespace BabyKit.DataModel
{
    // Used for weight and height
    [DataContract]
    class ConstellationInfo
    {
        [DataMember(Name = "description")]
        internal string Description;
    }

}
