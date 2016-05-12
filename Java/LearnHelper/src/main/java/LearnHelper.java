//package src.main.java;

//import org.apache.commons.codec.binary.Base64;
//import org.jsoap.*;
import org.jsoup.Connection;
import org.jsoup.Connection.*;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.apache.log4j.Logger;

import java.io.IOException;


/**
 * Created by dlin on 5/12/16.
 */
public class LearnHelper {

    private static org.apache.log4j.Logger log = Logger.getLogger(LearnHelper.class);

    public static void main(String[] args)
    {
        String userId = "administrator";
        String password = "IzCClI-1C0jv4A";
        //String encodedPwd = new String(Base64.encodeBase64(password.getBytes()));
        try {
            String host = "https://learn-pf-saas01.blackboard.com";
            String loginUrl = host + "/webapps/login";

            Connection.Response res = Jsoup.connect(loginUrl)
                    .header("Content-Type", "application/x-www-form-urlencoded")
                    .data("user_id", userId)
                    .data("password", password)
                    .data("login", "Sign In")
                    .data("new_loc", "")
                    .data("action", "login")
//                    .data("encoded_pw", password)
                    .method(Method.POST)
                    .execute();

            Document doc1 = res.parse();
//            System.out.println(res.hasHeader("X-Blackboard-product"));
//            System.out.println(res.header("X-Blackboard-product"));

            log.debug(res.hasHeader("X-Blackboard-product"));
            log.debug(res.header("X-Blackboard-product"));

//            String adminUrl = host + "/ultra/admin";
//            //This will get you cookies
//            Map<String, String> loginCookies = res.cookies();
//
//
//
//            //And this is the easiest way I've found to remain in session
//            Document doc2 = Jsoup.connect(adminUrl)
//                    .cookies(loginCookies)
//                    .get();
        } catch (IOException e) {
            e.printStackTrace();
        }
        System.out.println("hello world");
    }
}
