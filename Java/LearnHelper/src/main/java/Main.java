import org.apache.log4j.Logger;

/**
 * Created by dlin on 5/13/16.
 */
public class Main {

    private static org.apache.log4j.Logger log = Logger.getLogger(Main.class);
    public static void main(String[] args)
    {
        LearnHelper learnHelper = new LearnHelper("learn-pf-saas01_user_config.properties");
        learnHelper.ParseConfigInfo();
        log.debug(learnHelper.GetLearnVersion(learnHelper.GetHost()));
        //log.debug(learnHelper.GetLearnVersionREST(learnHelper.GetHost()));
        log.debug(learnHelper.GetLearnVersionHttpClient(learnHelper.GetHost()));

        log.debug(learnHelper.GetUsersNum());
    }
}
