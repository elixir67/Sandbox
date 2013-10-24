using BabyKit.Utility;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;
using Windows.Storage;

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

    class BabyManager
    {
        private static readonly string BABYINFO_PATH = "BabyInfo.json";

        internal static BabyInfo _baby;

        // TODO implement the singletion
        //public static BabyInfo BabyInstance()
        //{
        //    //if (null == _baby)
        //    //{
        //    //    _baby = new BabyInfo();
        //    //}
        //    return _baby;
        //}

        public static async Task<BabyInfo> Load()
        {
            var storageFolder = KnownFolders.DocumentsLibrary;

            var file = storageFolder.GetFileAsync(BABYINFO_PATH);

            _baby = await FileHelper.LoadData<BabyInfo>(BABYINFO_PATH);
            return _baby;
        }

        public static void Save()
        {
            FileHelper.SaveData(BABYINFO_PATH, _baby);
        }

        //class BabyInstanceCreator()
        //{
        //    internal static BabyInfo _baby = null;

        //    internal static BabyInfo Create()
        //    {
        //        _baby = new BabyInfo();
        //        Load();
        //    }
        //}
    }

}
