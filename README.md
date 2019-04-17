# Parallel indexing of text files
<h4>Description:</h4>
<p>
Indexes words from input data filename by alphabetical and usage count order.<br/>
Command line input: config_filename, which has:<br/>
    <ul>
        <li>input data filename (supports zip and txt format)</li>
        <li>output filename by alphabet</li>
        <li>output filename by count (from most occuring word to least one)</li>
        <li>number of threads to utilize</li>
    </ul>
</p>
<h4>Requirements</h4>
<ul>
    <li>Boost.Locale >= 1.68.0</li>
    <li>ICU >= 62.1</li>
    <li>libarchive >= 3.3.3</li>
</ul>
<h4>How to build&run</h4>
<ul>
    <li>mkdir build; cd build; cmake ..; make -j4</li>
    <li>./parallel_indexing &lt;path_to_config_file&gt;</li>
</ul>
</br>
<footer> © Created by Andrii Maistruk and Anatolii Iatsuk.</footer>