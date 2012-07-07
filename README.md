RS-Video-Analyser
==================

Video Analyser created for Rohde &amp; Schwarz.  Modified to make it more useful for general use and simpler to demonstrate.  There are 3 applications.  These applications were created to serve as utility extensions for existing R&S applications.  The final versions of the applications are with R&S, these here are a couple of versions back - with a couple of bugs remaining.  However, they are fully functional.

The db directory contains an SQLite database that all three applications use to read and/or write to.
streamAnalyser:  (Windows only) Scans one or more directories for supported video files and records video characteristics to a database.  Use third-party library; MediaInfo.
libraryBrowser:  Allows a user to find a given video file using filter criteria.
tableEditor:  Allows the user to manually edit any database entries.