#ifndef WXDYNSTRINGHASHMAP_H
#define WXDYNSTRINGHASHMAP_H

#include <wx/wx.h>
#include <stdexcept>

class wxDynStringHashMap
{
public:
    wxDynStringHashMap() = default;
    wxDynStringHashMap(const wxArrayString& keys, const wxArrayString& vals);

    const wxArrayString& keys() const;
    const wxArrayString& values() const;

    wxString& operator[](const wxString& key);
    const wxString& operator[](const wxString& key) const;

    void insertOrUpdate(const wxString& key, const wxString& value);

private:
    wxArrayString keys_;
    wxArrayString vals_;

    size_t findKey(const wxString& key) const;
    size_t findOrInsertKey(const wxString& key);
};

inline wxDynStringHashMap::wxDynStringHashMap(const wxArrayString& keys, const wxArrayString& vals)
{
    if (keys.GetCount() != vals.GetCount())
    {
        wxLogError("Keys and values arrays must have the same length");
        throw std::invalid_argument("Keys and values arrays must have the same length");
    }

    keys_ = keys;
    vals_ = vals;
}

inline const wxArrayString& wxDynStringHashMap::keys() const
{
    return keys_;
}

inline const wxArrayString& wxDynStringHashMap::values() const
{
    return vals_;
}

inline wxString& wxDynStringHashMap::operator[](const wxString& key)
{
    size_t index = findKey(key);
    return vals_[index];
}

inline const wxString& wxDynStringHashMap::operator[](const wxString& key) const
{
    size_t index = findKey(key);
    if (index == wxNOT_FOUND)
    {
        wxLogError("Key not found");
        throw std::out_of_range("Key not found");
    }
    return vals_[index];
}

inline void wxDynStringHashMap::insertOrUpdate(const wxString& key, const wxString& value)
{
    size_t index = findOrInsertKey(key);
    vals_[index] = value;
}

inline size_t wxDynStringHashMap::findKey(const wxString& key) const
{
    for (size_t i = 0; i < keys_.GetCount(); ++i)
    {
        if (keys_[i] == key)
        {
            return i;
        }
    }
    return wxNOT_FOUND;
}

inline size_t wxDynStringHashMap::findOrInsertKey(const wxString& key)
{
    size_t index = findKey(key);
    if (index == wxNOT_FOUND)
    {
        keys_.Add(key);
        vals_.Add(wxString());
        return keys_.GetCount() - 1; // Return the index of the newly added key
    }
    return index;
}

#endif // WXDYNSTRINGHASHMAP_H
