//package src.main.java;

//import org.apache.commons.codec.binary.Base64;
//import org.jsoap.*;

import org.apache.log4j.Logger;
import org.jsoup.Connection.Method;
import org.jsoup.Connection.Response;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;

import java.io.IOException;
import java.io.InputStream;
import java.util.Map;
import java.util.Properties;


/**
 * Created by dlin on 5/12/16.
 */
public class LearnHelper {

    private static org.apache.log4j.Logger log = Logger.getLogger(LearnHelper.class);

    public static void main(String[] args)
    {
        GetLearnVersion();
    }

    private static void GetConfigInfo()
    {
        Properties prop = new Properties();
        String propFileName = "learn-pf-saas01_user_config.properties";
        try {
            InputStream inputStream = LearnHelper.class.getClassLoader().getResourceAsStream(propFileName);
            if (inputStream != null) {
                prop.load(inputStream);

                // get the property value and print it out
                String host = prop.getProperty("hosts");
                log.debug(host);


                String users = prop.getProperty("test.threads");
                log.debug(users);

            }
            else {
                log.debug("Cannot locate "+propFileName);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void GetLearnVersion() {
        String userId = "administrator";
        String password = "IzCClI-1C0jv4A";
        //String encodedPwd = new String(Base64.encodeBase64(password.getBytes()));
        try {
            String host = "https://learn-pf-saas01.blackboard.com";
            String loginUrl = host + "/webapps/login/";

            Response res = Jsoup.connect(loginUrl)
                    .header("Content-Type", "application/x-www-form-urlencoded")
//                    .header("Cache-Control", "no-cache")
//                    .header("'Connection'", "keep-alive")
                    .data("user_id", userId)
                    .data("password", password)
                    .data("login", "Sign In")
                    .data("new_loc", "")
                    .data("action", "login")
//                    .data("encoded_pw", password)
                    .method(Method.POST)
                    .execute();

            Document doc1 = res.parse();

            log.debug(res.hasHeader("X-Blackboard-product"));
            String productName = res.header("X-Blackboard-product");
            log.debug(productName);

            String version = productName.substring(productName.indexOf("; ")+2);
            log.debug(version);

            //String adminUrl = host + "/ultra/admin/";

            // How to send REST request?
//            String adminUrl = host + "/learn/api/v1/utilities/systemInfo";
//            //This will get you cookies
//            Map<String, String> loginCookies = res.cookies();
//
//            //And this is the easiest way I've found to remain in session
//            Response res2 = Jsoup.connect(adminUrl)
//                    .header("Content-Type", "Mimetype=application/json;charset=UTF-8")
//                    .cookies(loginCookies)
//                    .method(Method.GET)
//                    .execute();
//
//            log.debug(res2.statusCode());
//            log.debug(res2.body());

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
