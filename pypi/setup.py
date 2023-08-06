import setuptools

setuptools.setup(
    name="seuif97",
    version="1.3.0",
    author="Cheng Maohua",
    author_email="cmh@seu.edu.cn",
    url="https://github.com/thermalogic/SEUIF97",
    packages=['seuif97'],
    package_data={'': ['*.so','*.dll','README.rst']},
    license="MIT",
    description="IAPWS-IF97 high-speed shared library(Windows64/32,Linux64),Python API",
    long_description=open("./seuif97/README.rst", "r",encoding="utf8").read(),   
    platforms=["Windows64/32","Linux64"],
    classifiers=[
        "Programming Language :: Python :: 3",
        "Programming Language :: C",
        "Topic :: Scientific/Engineering",
        "Topic :: Scientific/Engineering :: Chemistry",
        "Topic :: Scientific/Engineering :: Physics",
        "Topic :: Software Development :: Libraries :: Python Modules"
    ]
)
