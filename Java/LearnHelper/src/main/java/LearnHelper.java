import org.jsoup.Connection.Method;
import org.jsoup.Connection.Response;
import org.jsoup.Jsoup;
import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;


/**
 * Created by dlin on 5/12/16.
 */
public class LearnHelper {

    private String host;
    private int usersNum;
    private String config;

    public LearnHelper(String config)
    {
        this.config = config;
    }

    public String GetHost()
    {
        return host;
    }

    public int GetUsersNum()
    {
        return usersNum;
    }

    public void ParseConfigInfo()
    {
        Properties prop = new Properties();
        //String propFileName = "learn-pf-saas01_user_config.properties";
        String propFileName = config;
        try {
            InputStream inputStream = LearnHelper.class.getClassLoader().getResourceAsStream(propFileName);
            if (inputStream != null) {
                prop.load(inputStream);

                // get the property value and print it out
                host = prop.getProperty("hosts");
                String users = prop.getProperty("test.threads");
                usersNum = Integer.parseInt(users);
            }
            else {
                System.out.println("Cannot locate " + propFileName);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static String GetLearnVersion(String host) {
        String userId = "administrator";
        String password = "IzCClI-1C0jv4A";
        try {
            //String host = "https://learn-pf-saas01.blackboard.com";
            String loginUrl = "https://" + host + "/webapps/login/";

            Response res = Jsoup.connect(loginUrl)
                    .header("Content-Type", "application/x-www-form-urlencoded")
                    .data("user_id", userId)
                    .data("password", password)
                    .data("login", "Sign In")
                    .data("new_loc", "")
                    .data("action", "login")
                    .method(Method.POST)
                    .execute();

            String productName = res.header("X-Blackboard-product");
            //log.debug(productName); // sample output: Blackboard Learn &#8482; 3000.3.0-rel.45+a7bf6a1

            String version = productName.substring(productName.indexOf("; ")+2);
            //log.debug(version);

            return version;

        } catch (IOException e) {
            e.printStackTrace();
        }

        return null;
    }

//    public static void GetRESTRequest() {
//        //String adminUrl = host + "/ultra/admin/";
//
//        // How to send REST request?
////            String adminUrl = host + "/learn/api/v1/utilities/systemInfo";
////            //This will get you cookies
////            Map<String, String> loginCookies = res.cookies();
////
////            //And this is the easiest way I've found to remain in session
////            Response res2 = Jsoup.connect(adminUrl)
////                    .header("Content-Type", "Mimetype=application/json;charset=UTF-8")
////                    .cookies(loginCookies)
////                    .method(Method.GET)
////                    .execute();
////
////            log.debug(res2.statusCode());
////            log.debug(res2.body());
//    }
}
