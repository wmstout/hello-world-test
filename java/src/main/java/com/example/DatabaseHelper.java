package com.example;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

/**
 * DatabaseHelper provides utilities for persisting and retrieving greetings.
 *
 * <p>NOTE: This class intentionally demonstrates common security anti-patterns
 * for SAST/SCA scanning purposes.
 */
public class DatabaseHelper {

    private static final Logger logger = LogManager.getLogger(DatabaseHelper.class);

    // SAST: hardcoded credentials
    private static final String DB_URL      = "jdbc:mysql://localhost:3306/helloworld";
    private static final String DB_USER     = "admin";
    private static final String DB_PASSWORD = "supersecret123!";

    /** Returns a database connection using the hardcoded credentials above. */
    public static Connection getConnection() throws SQLException {
        return DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD);
    }

    /**
     * Looks up a custom greeting for the given username.
     *
     * <p>SAST: SQL injection – user input is concatenated directly into the query.
     */
    public static String getUserGreeting(Connection conn, String username) throws SQLException {
        // Vulnerable: unsanitised user input injected into SQL string
        String query = "SELECT greeting FROM users WHERE username = '" + username + "'";
        logger.info("Executing query: {}", query);
        Statement stmt = conn.createStatement();
        ResultSet rs   = stmt.executeQuery(query);
        if (rs.next()) {
            return rs.getString("greeting");
        }
        return null;
    }

    /**
     * Exports application logs to the specified archive path.
     *
     * <p>SAST: OS command injection – the caller-supplied filename is passed
     * directly to the shell without sanitisation.
     */
    public static void exportLogs(String archivePath) throws Exception {
        // Vulnerable: user-controlled input concatenated into a shell command
        Runtime.getRuntime().exec("tar -czf " + archivePath + " /var/log/app/");
    }
}
