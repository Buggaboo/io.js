package nl.sison.android.iojs;


/**
 * Created by jasm on 1/22/15.
 */
public class IoJsJni {

    static {
        System.loadLibrary("iojs");
    }

    public static native int start(int argc, String[] argv);
    public static native int createLocalSocket(String where); // int socket(AF_LOCAL, SOCKET_STREAM, 0);

}
