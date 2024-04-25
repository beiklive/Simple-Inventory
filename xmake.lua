add_rules("mode.debug", "mode.release")


target("Inventory")
    add_rules("qt.widgetapp")
    add_includedirs("inc")
    add_files("src/*.cpp")
    add_files("ui/*.ui")
    -- add files with Q_OBJECT meta (only for qt.moc)
    add_files("inc/*.h")