import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.HttpClient;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.CloseableHttpResponse;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.impl.client.HttpClients;
import org.apache.http.impl.client.SystemDefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;
import org.apache.log4j.Logger;
import org.json.JSONObject;
import org.jsoup.Connection.Method;
import org.jsoup.Connection.Response;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;

import javax.net.ssl.HttpsURLConnection;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.URL;
import java.net.URLEncoder;
import java.util.*;


/**
 * Created by dlin on 5/12/16.
 */
public class LearnHelper {

    private String host;
    private int usersNum;
    private String config;
    private static org.apache.log4j.Logger log = Logger.getLogger(LearnHelper.class);
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

    public String GetLearnVersion(String host) {
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

            String version = productName.substring(productName.indexOf("; ") + 2);
            //log.debug(version);

            return version;

        } catch (IOException e) {
            e.printStackTrace();
        }
        return "2015.0.0-ci.22+e8520f1";
    }

    public String GetLearnVersionHttpClient(String host) {
        String userId = "administrator";
        String password = "IzCClI-1C0jv4A";
        try {
            //String host = "https://learn-pf-saas01.blackboard.com";
            String loginUrl = "https://" + host + "/webapps/login/";

            CloseableHttpClient client = HttpClients.createDefault();
            HttpPost post = new HttpPost(loginUrl);

            post.setHeader("Content-Type", "application/x-www-form-urlencoded");
            List<NameValuePair> urlParameters = new ArrayList<NameValuePair>();
            urlParameters.add(new BasicNameValuePair("user_id", userId));
            urlParameters.add(new BasicNameValuePair("password", password));
            urlParameters.add(new BasicNameValuePair("login", "Sign In"));
            urlParameters.add(new BasicNameValuePair("new_loc", ""));
            urlParameters.add(new BasicNameValuePair("action", "login"));

            post.setEntity(new UrlEncodedFormEntity(urlParameters));

            CloseableHttpResponse res = client.execute(post);
            log.debug(res.getStatusLine().getStatusCode());
            String productName = res.getFirstHeader("X-Blackboard-product").getValue();
            log.debug(productName); // sample output: Blackboard Learn &#8482; 3000.3.0-rel.45+a7bf6a1

            res.close();
            String version = productName.substring(productName.indexOf("; ") + 2);
            log.debug(version);



            String infoUrl = "https://" + host + "/learn/api/v1/utilities/systemInfo";
            HttpGet get = new HttpGet(infoUrl);
            res = client.execute(get);

            log.debug(res.getStatusLine().getStatusCode());
            BufferedReader rd = new BufferedReader(new InputStreamReader(res.getEntity().getContent()));

            StringBuffer result = new StringBuffer();
            String line = "";
            while ((line = rd.readLine()) != null) {
                result.append(line);
            }

            //log.debug(result.toString());
            res.close();
            JSONObject o = new JSONObject(result.toString());
            log.debug("ultraUiEnabled:" + o.get("ultraUiEnabled"));
            log.debug("adminPanel:" + o.getJSONObject("classicUrls").get("adminPanel"));
            return version;

        } catch (IOException e) {
            e.printStackTrace();
        }
        return "2015.0.0-ci.22+e8520f1";
    }

    public String GetLearnVersionREST(String host) {
        String userId = "administrator";
        String password = "IzCClI-1C0jv4A";
        try {
            //String host = "https://learn-pf-saas01.blackboard.com";
            String loginUrl = "https://" + host + "/webapps/login/";
            URL url = new URL(loginUrl);
            HttpsURLConnection conn = (HttpsURLConnection)url.openConnection();
            conn.setUseCaches(false);
            conn.setRequestMethod("POST");
            conn.setRequestProperty("Content-Type", "application/x-www-form-urlencoded");
            conn.setDoOutput(true);

            Map<String,String> params = new LinkedHashMap<java.lang.String, java.lang.String>();
            params.put("user_id", userId);
            params.put("password", password);
            params.put("login", "Sign In");
            params.put("new_loc", "");

            StringBuilder postData = new StringBuilder();
            for (Map.Entry<String,String> param : params.entrySet()) {
                if (postData.length() != 0) postData.append('&');
                postData.append(URLEncoder.encode(param.getKey(), "UTF-8"));
                postData.append('=');
                postData.append(URLEncoder.encode(String.valueOf(param.getValue()), "UTF-8"));
            }
            byte[] postDataBytes = postData.toString().getBytes("UTF-8");
            conn.getOutputStream().write(postDataBytes);


            String result = "";
            String line;
            BufferedReader reader = new BufferedReader(new InputStreamReader(conn.getInputStream()));

            while ((line = reader.readLine()) != null) {
                result += line;
                //log.debug(line);
            }
            reader.close();

            Document doc = Jsoup.parse(result);
//            Iterator<Element> opts = doc.select("option").iterator();
//            for (;opts.hasNext();) {
//                Element item = opts.next();
//                if (item.hasAttr("value")) {
//                    System.out.println(item.attr("value"));
//                }
//            }
            //String productName = res.header("X-Blackboard-product");
            //log.debug(productName); // sample output: Blackboard Learn &#8482; 3000.3.0-rel.45+a7bf6a1

            //String version = productName.substring(productName.indexOf("; ")+2);
            //log.debug(version);
            String version = null;
            return version;

        } catch (IOException e) {
            e.printStackTrace();
        }
        return "2015.0.0-ci.22+e8520f1";
    }
}
