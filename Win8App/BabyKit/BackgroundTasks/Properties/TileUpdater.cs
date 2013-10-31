using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.ApplicationModel.Background;
using Windows.UI.Notifications;

namespace BackgroundTasks
{
    public sealed class TileUpdater : IBackgroundTask
    {
        public void Run(IBackgroundTaskInstance taskInstance)
        {
            var defferal = taskInstance.GetDeferral();

            var updater = TileUpdateManager.CreateTileUpdaterForApplication();
            updater.EnableNotificationQueue(true);

            updater.Clear();

            for (int i = 1; i < 6; i++)
            {
                var tile = TileUpdateManager.GetTemplateContent(TileTemplateType.TileSquareText02);
                tile.GetElementsByTagName("text")[0].InnerText = "Tile " + i;
                tile.GetElementsByTagName("text")[1].InnerText = DateTime.Now.ToString("hh-mm");

                updater.Update(new TileNotification(tile));
            }

            defferal.Complete();
        }
    }
}
