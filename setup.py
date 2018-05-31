import setuptools

setuptools.setup(
    name="seuif97",
    version="1.0.0.0.3",
    author="Cheng Maohua",
    author_email="cmh@seu.edu.cn",
    url="https://github.com/PySEE/SEUIF97",
    packages=['seuif97'],
    package_data={'': ['*.so','*.dll']},
    license="MIT",
    description='IAPWS-IF97 high-speed shared library(Windows64,Linux64) in ANSI C,Python API',
    long_description='IAPWS-IF97 high-speed shared library(Windows64,Linux64) in ANSI C,Python API',                  
    platforms=["Windows64","Linux64"],
    classifiers=[
        "Programming Language :: Python :: 3",
        "Programming Language :: C",
        "Topic :: Scientific/Engineering",
        "Topic :: Scientific/Engineering :: Chemistry",
        "Topic :: Scientific/Engineering :: Physics",
        "Topic :: Software Development :: Libraries :: Python Modules"
    ]
)
