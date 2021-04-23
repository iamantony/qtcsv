import qbs
import qbs.File

Product {
    type: "staticlibrary"
    name: "qtcsv"
    Depends { name: "cpp" }
    cpp.optimization: qbs.buildVariant == "debug" ? "none" : "fast"
    cpp.debugInformation: qbs.buildVariant == "debug" ? true : false
    cpp.cxxLanguageVersion: "c++11"
    cpp.defines: [
        "QTCSV_STATIC",
        "QTCSV_LIBRARY",
    ]
    Depends {
        name: "Qt"
        submodules: ["core"]
    }

    Export {
        Depends { name: "cpp" }
        cpp.includePaths: [product.sourceDirectory, product.sourceDirectory+"/include"]
        Properties {
            condition: product.type.contains("staticlibrary")
            cpp.defines: ["QTCSV_STATIC"]
        }
    }

    cpp.includePaths: [product.sourceDirectory, product.sourceDirectory+"/include"]

    files: [
    ]
    Group {
        name: "C++ Sources";
        files: [
            "qtcsv/contentiterator.cpp",
            "qtcsv/reader.cpp",
            "qtcsv/stringdata.cpp",
            "qtcsv/variantdata.cpp",
            "qtcsv/writer.cpp",
        ]
        fileTags: ["cpp"];
    }
    Group {
        name: "C++ Headers";
        files: [
            "include/qtcsv/abstractdata.h",
            "include/qtcsv/qtcsv_global.h",
            "include/qtcsv/reader.h",
            "include/qtcsv/stringdata.h",
            "include/qtcsv/variantdata.h",
            "include/qtcsv/writer.h",
            "qtcsv/contentiterator.h",
            "qtcsv/filechecker.h",
            "qtcsv/symbols.h",
        ]
        fileTags: ["hpp"];
    }

    Group {
        fileTagsFilter: product.type
        qbs.install:  true
        qbs.installDir:  "lib/"
        fileTags: ["header"]
    }
    Group {
        fileTagsFilter: "hpp"
        qbs.install:  true
        qbs.installDir:  "include/"
    }
}
